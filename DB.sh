#!/bin/bash

# File where student data will be stored
DB_FILE="student_db.txt"

# Create the database file if it does not exist
if [ ! -f "$DB_FILE" ]; then
    touch "$DB_FILE"
    echo "Database file created: $DB_FILE"
fi

# Function to insert a new student record
insert_student() {
    read -p "Enter Roll Number: " roll
    read -p "Enter Name: " name
    read -p "Enter Course: " course
    
    # Check if roll number already exists
    if grep -q "^$roll," "$DB_FILE"; then
        echo "Error: Roll Number $roll already exists."
    else
        echo "$roll,$name,$course" >> "$DB_FILE"
        echo "Student record inserted successfully."
    fi
}

# Function to delete a student record
delete_student() {
    read -p "Enter Roll Number to delete: " roll
    if grep -q "^$roll," "$DB_FILE"; then
        # Delete the line containing the roll number
        grep -v "^$roll," "$DB_FILE" > temp && mv temp "$DB_FILE"
        echo "Student record deleted successfully."
    else
        echo "Error: Roll Number $roll not found."
    fi
}

# Function to update a student record
update_student() {
    read -p "Enter Roll Number to update: " roll
    if grep -q "^$roll," "$DB_FILE"; then
        read -p "Enter new Name: " name
        read -p "Enter new Course: " course
        
        # Replace the line with new data
        grep -v "^$roll," "$DB_FILE" > temp && mv temp "$DB_FILE"
        echo "$roll,$name,$course" >> "$DB_FILE"
        echo "Student record updated successfully."
    else
        echo "Error: Roll Number $roll not found."
    fi
}

# Function to search for a student record
search_student() {
    read -p "Enter Roll Number to search: " roll
    if grep -q "^$roll," "$DB_FILE"; then
        grep "^$roll," "$DB_FILE"
    else
        echo "Error: Roll Number $roll not found."
    fi
}

# Main script loop
while true; do
    echo "Choose an operation:"
    echo "1) Insert"
    echo "2) Delete"
    echo "3) Update"
    echo "4) Search"
    echo "5) Exit"
    read -p "Enter your choice: " choice

    case $choice in
        1) insert_student ;;
        2) delete_student ;;
        3) update_student ;;
        4) search_student ;;
        5) echo "Exiting..."; break ;;
        *) echo "Invalid choice, please try again." ;;
    esac
done
