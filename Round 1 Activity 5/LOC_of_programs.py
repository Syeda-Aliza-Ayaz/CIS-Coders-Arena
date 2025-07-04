import time
import os # to get the filename

files = []
fileName = " "
print("-------------------- PYTHON FILE LOC COUNT --------------------")
while(True):
    fileName = input("Enter the name of python file (Press Enter to terminate): ")
    if(fileName == ""):
        break
    if(not fileName.endswith(".py")):
        print("‼️  Invalid File Name: The file must end with \".py\"")
        continue
    files.append(fileName)

all_files_info = []
file_info = {}
for name in files:
    lines = 0
    start_time = time.time()
    try:
        with open(name, "r", encoding="utf-8", errors="ignore") as file:
            for line in file:
                line = line.strip()
                if line == "" or line.startswith("#"):
                    continue
                lines += 1
    except FileNotFoundError:
        print("‼️  Could not open", name)
        continue
    end_time = time.time()
    totalTime = end_time - start_time

    file_info = {}
    file_info["Name"] = name
    file_info["LOC"] = lines
    file_info["Time"] = totalTime

    all_files_info.append(file_info)

    print(f"Processed file {name}: LOC = {lines}, Time: {totalTime:.4f} seconds")

slowest = all_files_info[0] ## Assuming first one is slowest
fastest = all_files_info[0] ## Assuming first one is fastest too

for info in all_files_info:
    if(fastest["Time"] < info["Time"]):
        fastest = info
    if(slowest["Time"] > info["Time"]):
        slowest = info

print("===================== SUMMARY =====================")
print("---------------------------------------------------")

if (len(all_files_info)):
    for info in all_files_info:
            base_name = os.path.basename(info["Name"])
            print(f"{base_name:20} LOC: {info['LOC']:5}  Time: {info['Time']:.4f} sec")
    print("---------------------------------------------------\n")

    print("\nFastest File  :", os.path.basename(fastest['Name']), f"(Time: {fastest['Time']:.4f} sec)")
    print("Slowest File  :", os.path.basename(slowest['Name']), f"(Time: {slowest['Time']:.4f} sec)")
    if(fastest != slowest):
        print("Observation: More Lines of Code = More Time to Process")
    else:
        print("Observation: All files took the same time to process")


else:
    print("‼️  No valid files were processed.")