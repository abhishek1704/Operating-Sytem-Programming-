  #!/bin/sh

filename="database.txt"
y=2020

line () {
  printf "\n---------------------------------------------------------------------------\n"
}

newline () {
  printf "\n"
}

# Function to add a single record

Add () {

  while [ -z $name ]; do
    echo " "
    echo "Enter a name  : "
    read name
  done 
  
  pat='^[0-9]+$'
  while [ -z $phone ]
  do
    echo "Enter a phone : "
    read phone
    if [ ${#phone} -ne 10 ]  # Phone number validation
    then 
      echo "Enter a valid phone : "
      read phone
    fi
  done 

  read -p "Enter a address : " address
  while [ -z $address ]; do
    echo "Enter a address : "
    read address
  done 

  echo "Enter the start date of booking : "
  read -p "Day : " d
  while [ $d  -le 0 ] || [ $d -ge 32 ]; do # Day validation
    read -p "Enter a valid day : " d
  done

  read -p "Month : " m
  while [ $m  -le 0 ] || [ $m -ge 13 ]; do # Month validation
    read -p "Enter a valid month : " m
  done

  sDate="$d/$m/$y"

  echo "Enter the end date of booking : "
  read -p "Day : " d
  while [ $d  -le 0 ] || [ $d -ge 32 ]; do
    read -p "Enter a valid day : " d
  done

  read -p "Month : " m
  while [ $m  -le 0 ] || [ $m -ge 13 ]; do
    read -p "Enter a valid month : " m
  done

  eDate="$d/$m/$y"

  echo "Enter the room type out of:"
  newline
  echo "    Type   |  Rate (Rs./day) "
  echo "----------------------------"
  newline
  printf "1. Delux\t5000"
  printf "\n2. Standard\t200"
  printf "\n3. Budget\t800" 
  newline
  read -p "Enter the type : " roomType 

  while [ -z $roomType ]; do
    echo "Enter the room type again : "
    read roomType
  done 

  printf "\n%8s %10s %10s %13s %13s %10s" $name $phone $address $sDate $eDate $roomType>>"$filename"

  unset name
  unset phone
  unset address
  unset d
  unset m
  unset sDate
  unset eDate
  unset roomType

}

# Display records

Display () {
  newline
  line
  printf "  Name\t| Phone\t\t| Address  | Start Date | End Date | Room Type"
  line
  cat "$filename"
  newline
  line
}

# Search for a record in a file using phone number as a key

Search () {
 
  newline
  read -p "Enter phone number to search : " key 

  result=$(grep -r -w "$key" "$filename") 

  if [ -n "$result" ]; then
      printf '\nRecord found !\n'
      printf '\n%s\n' "$result"
  else
      printf '\nNo match found !\n'
  fi
}

# Deleting a record in a file using phone number as a key

Delete () {

  newline
  read -p "Enter a phone number to Delete : " key

  result=$(grep -r -w "$key" "$filename") 

  if [ -n "$result" ]; then
      printf '\nRecord found !\n'
      printf '\n%s\n' "$result"
      sed -i '/'$key'/d' "database.txt"
      printf "\nDeleted successfully !\n"
  else
      printf '\nNo match found !\n'
  fi

} 

# Modify a record in a file using phone number as a key

Modify () {

  newline
  read -p "Enter a phone number to modify a record : " key
  result=$(grep -r -w "$key" "$filename") 

  if [ -n "$result" ]; then
      printf '\nRecord found !\n'
      printf '\nModify the record :\n'
      read -p "Enter a name : " name
      while [ -z $name ]; do
        echo " Enter a name : "
        read name
      done 

      pat='^[0-9]+$'
      while [ -z $phone ]
      do
        echo "Enter a phone : "
        read phone
        if [ ${#phone} -ne 10 ]  # Phone number validation
        then 
          echo "Enter a valid phone : "
          read phone
        fi
      done 

      read -p "Enter a address : " address
      while [ -z $address ]; do
        echo " Enter a address : "
        read address
      done 

      echo "Enter the start date of booking : "
      read -p "Day : " d
      while [ $d  -le 0 ] || [ $d -ge 32 ]; do # Day validation
        read -p "Enter a valid day : " d
      done

      read -p "Month : " m
      while [ $m  -le 0 ] || [ $m -ge 13 ]; do # Month validation
        read -p "Enter a valid month : " m
      done

      sDate="$d/$m/$y"

      echo "Enter the end date of booking : "
      read -p "Day : " d
      while [ $d  -le 0 ] || [ $d -ge 32 ]; do
        read -p "Enter a valid day : " d
      done

      read -p "Month : " m
      while [ $m  -le 0 ] || [ $m -ge 13 ]; do
        read -p "Enter a valid month : " m
      done

      eDate="$d/$m/$y"

      echo "Following categories of rooms are available:"
      newline
      echo "    Type   |  Rate (Rs./day) "
      echo "----------------------------"
      newline
      printf "1. Delux\t5000/day\n2. Standard\t2000/day\n3. Budget\t800/day" 
      newline
      read -p "Enter the room type : " roomType

      while [ -z $roomType ]; do
        echo "Enter the room type again : "
        read roomType
      done      

      sed -i '/'$key'/c\'$name'   '$phone'   '$address'   '$sDate'   '$eDate'   '$roomType'' $filename
  else
      newline
      printf 'No match found !\n'
  fi

}


# Sorting records with choice 

Sort () {

  newline
  echo "Sorting by : "
  echo "1. Name"
  echo "2. Phone number"
  echo "3. Address"
  echo "4. Start date"
  echo "5. End date" 
  echo "6. Room type"

  newline
  read -p "Enter your choice : " choice
  echo "Records after sorting : "

  newline
  line
  echo "  Name  | Phone  |    Address   | Start Date | End Date | Room Type"
  line
  case "$choice" in
    1) 
        sort -s -k1 $filename
        ;;
    2) 
        sort -sn -k2 $filename 
        ;;
    3) 
        sort -s -k3 $filename
        ;;
    4) 
        sort -sn -k4 $filename
        ;;
    5)
        sort -sn -k5 $filename
        ;;
    6)
        sort -s -k6 $filename
        ;;     
    *) 
      newline
      echo "Unkown choice !" 
      ;;
  esac

}

while true
do
  newline
  echo "Menu: "
  echo "1. Create a record"
  echo "2. View hotel record"
  echo "3. Add a record"
  echo "4. Delete a record"
  echo "5. Modify a record"
  echo "6. Search a record"  
  echo "7. Sort the records"
  echo "8. Exit"

  read -p "Enter your choice : " choice

  case "$choice" in
    1) 
      newline
    	read -p "Enter number of records to create : " n
    	while [ $n -ge 1 ]; do
      		 Add 
      		 n=$(( $n - 1 ))
      	done
       	;;
    2) 
        if [ -s "$filename" ]; then
          Display
        else
          newline
           echo "Database is empty !"                 
        fi
        ;;
    3) 
        Add 
        ;;
    4) 
        Delete
        ;;
    5) 
        Modify
        ;;
    6)
        Search
        ;;
    7)
       	Sort
        ;;     
    8)
      	break
      ;;
    *) 
      newline
      echo "Unkown choice !" 
      ;;
        esac
done
