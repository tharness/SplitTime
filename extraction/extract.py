#!/usr/bin/env python3
"""Extract saved SplitTime shots from an Arduino over USB serial."""

import csv
import time
from datetime import datetime
from pathlib import Path

try:
	import serial
	from serial.tools import list_ports
except ImportError as error:
	raise SystemExit("pyserial is required: python3 -m pip install pyserial") from error


BAUD_RATE = 9600
SERIAL_STARTUP_DELAY_SECONDS = 2
SERIAL_TIMEOUT_SECONDS = 2
DATA_REQUEST = b"DATA_REQUEST"
DATA_REQUEST_RECEIVED = b"DATA_REQUEST RECEIVED"
DATA_START = b"DATA_START"
DATA_END = b"DATA_END"


def decode_shot(first_byte, second_byte):
	"""Decode one two-byte ShotBytes record from the Arduino."""
	if not 0 <= first_byte <= 255 or not 0 <= second_byte <= 255:
		raise ValueError("shot bytes must be in the range 0..255")

	position_code = first_byte >> 6
	position = {
		0: "Lead",
		1: "Second",
		2: "Third",
		3: "Skip",
	}[position_code]

	zone = ((first_byte >> 1) & 0x0F)
	zone_value = "HOG" if zone == 0 else "THROUGH" if zone == 11 else str(zone)

	split_hundredths = ((first_byte & 1) << 8) | second_byte
	return position, split_hundredths / 100, zone_value


def _payload_records(payload):
	"""Return records from either newline-separated or contiguous payloads."""
	if len(payload) % 4 == 0 and all(
		payload[index:index + 2] == b"\r\n"
		for index in range(2, len(payload), 4)
	):
		payload = b"".join(
			payload[index:index + 2] for index in range(0, len(payload), 4)
		)
	elif len(payload) % 3 == 0 and all(
		payload[index] in (10, 13) for index in range(2, len(payload), 3)
	):
		payload = b"".join(
			payload[index:index + 2] for index in range(0, len(payload), 3)
		)

	if len(payload) % 2:
		raise ValueError("data payload does not contain complete two-byte records")
	return [
		decode_shot(payload[index], payload[index + 1])
		for index in range(0, len(payload), 2)
	]


def extract_from_port(port_name):
	"""Request and decode all shots from one serial port."""
	with serial.Serial(port_name, BAUD_RATE, timeout=SERIAL_TIMEOUT_SECONDS) as connection:
		# Opening many Arduino USB serial ports resets the board.
		time.sleep(SERIAL_STARTUP_DELAY_SECONDS)
		connection.reset_input_buffer()
		connection.write(DATA_REQUEST + b"\n")
		response = connection.readline().strip()
		if response != DATA_REQUEST_RECEIVED:
			raise ValueError(f"unexpected response from {port_name}: {response!r}")

		if connection.readline().strip() != DATA_START:
			raise ValueError(f"{port_name} did not start a data transfer")

		payload = bytearray()
		deadline = time.monotonic() + SERIAL_TIMEOUT_SECONDS
		while True:
			if time.monotonic() >= deadline:
				raise TimeoutError(f"timed out waiting for DATA_END from {port_name}")
			byte = connection.read(1)
			if not byte:
				continue
			payload.extend(byte)
			if payload.endswith(DATA_END):
				records = _payload_records(payload[:-len(DATA_END)])
				if not records:
					raise ValueError(f"{port_name} returned no saved shot data")
				return records


def write_csv(records, output_path):
	with Path(output_path).open("w", newline="", encoding="utf-8") as output_file:
		writer = csv.writer(output_file)
		writer.writerow(("Shot", "Position", "Split", "Zone"))
		for shot_number, (position, split, zone) in enumerate(records, start=1):
			writer.writerow((shot_number, position, f"{split:.2f}", zone))


def main():
	ports = [port.device for port in list_ports.comports() if port.vid is not None]
	if not ports:
		raise SystemExit("No USB serial ports found")

	for port_name in ports:
		try:
			records = extract_from_port(port_name)
		except (OSError, ValueError, TimeoutError) as error:
			print(f"Skipping {port_name}: {error}")
			continue

		output_path = Path(__file__).resolve().parent / (
			f"SplitTime_{datetime.now():%Y-%m-%dT%H-%M}.csv"
		)
		write_csv(records, output_path)
		print(f"Extracted {len(records)} shots from {port_name} to {output_path}")
		return

	raise SystemExit("No SplitTime device responded to DATA_REQUEST")


if __name__ == "__main__":
	main()
