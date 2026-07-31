import csv
import tkinter as tk
from tkinter import filedialog

# ================= FILE SELECTION =================

root = tk.Tk()
root.withdraw()

print("Select Student Database")
student_file = filedialog.askopenfilename(
    title="Select Student Database",
    filetypes=[("CSV Files", "*.csv")]
)

print("Select Attendance File")
attendance_file = filedialog.askopenfilename(
    title="Select Attendance File",
    filetypes=[("CSV Files", "*.csv")]
)

# ================= LOAD STUDENTS =================

students = {}

with open(student_file, "r", newline="", encoding="utf-8") as f:

    reader = csv.DictReader(f)

    # remove accidental spaces
    reader.fieldnames = [field.strip()
                         for field in reader.fieldnames]

    for row in reader:

        clean_row = {
            k.strip(): v.strip()
            for k, v in row.items()
        }

        students[clean_row["ID"]] = clean_row["Name"]

# ================= PROCESS ATTENDANCE =================

processed = []
attended = set()

with open(attendance_file, "r",
          newline="",
          encoding="utf-8") as f:

    reader = csv.reader(f)

    for student_id, time in reader:

        student_id = student_id.strip()

        attended.add(student_id)

        if student_id in students:

            processed.append([
                student_id,
                students[student_id],
                time,
                "Present"
            ])

        else:

            processed.append([
                student_id,
                "UNKNOWN",
                time,
                "Present"
            ])

# ================= FIND ABSENTEES =================

for student_id, name in students.items():

    if student_id not in attended:

        processed.append([
            student_id,
            name,
            "",
            "Absent"
        ])

# ================= SAVE OUTPUT =================

output_file = filedialog.asksaveasfilename(
    title="Save Attendance Report",
    defaultextension=".csv",
    filetypes=[("CSV Files", "*.csv")]
)

with open(output_file,
          "w",
          newline="",
          encoding="utf-8") as f:

    writer = csv.writer(f)

    writer.writerow([
        "ID",
        "Name",
        "Time",
        "Status"
    ])

    writer.writerows(processed)

print("Attendance Report Generated Successfully")