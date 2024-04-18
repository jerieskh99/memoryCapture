import subprocess
import time
import datetime
import os


def capture_memory(period):
    while True:
        # Current timestamp for file naming
        timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")

        # Load the LiME module to capture memory
        subprocess.run(["sudo", "insmod", "/home/kali/LiME-master/src/lime-6.6.9-amd64.ko", 
                        "path=/tmp/memimage.mem", "format=raw"], check=True)

        # Define the memory dump file path and hex file path
        mem_dump_path = "/tmp/memimage.mem"
        hex_file_path = f"/home/kali/mempartial_{timestamp}.hex"

        # Wait a brief moment to ensure the memory dump file is fully written
        time.sleep(2)

        # Capture the memory segment and convert to hex
        # with open(hex_file_path, "w") as hex_file:
        #    subprocess.run(["sudo", "dd", "if=" + mem_dump_path, "bs=1M", "skip=1024", "count=12"],
        #                   stdout=subprocess.PIPE, check=True)
        #    subprocess.run(["xxd", "-p"], input=dd_process.stdout, stdout=hex_file)


        # Execute the dd and xxd commands in one line using a shell pipeline
        command = f"sudo dd if=/tmp/memimage.mem bs=1M skip=1024 count=12 | xxd -p > {hex_file_path}"
        subprocess.run(command, shell=True, check=True)

        # Unload the LiME module
        subprocess.run(["sudo", "rmmod", "lime"], check=True)

        # Delete the memory image file to free up space
        command = f"sudo rm /tmp/memimage.mem"
        subprocess.run(command, shell=True, check=True)

        # Wait for the specified period
        time.sleep(period)


def main():
    period = int(input("Enter the capture period in seconds: "))
    if period < 10:
         print("give me some time!! more than 10sec")
         return

    capture_memory(period)


if  __name__ == "__main__":
    main()
