#
# Use the 'ldd' command to verify 'shared libraries' exist.
#

#
# Is an input file name used?
#

arg1="unixinst"

if [ -z "$1" ]; then
   echo
   echo "Checking '$arg1' by default!"
else
   arg1="$1"
   echo
   echo "Checking '$arg1' binary file!"
fi

rm checklib.out 2> /dev/null

#
# Verify that the file to be checked exists and is an ELF
# binary executable which can be checked with 'ldd'.
#

if [ ! -f $arg1 ]; then
   echo
   echo "The '$arg1' binary exist does not exist!!"
   echo "Exiting script!"
   echo
   exit 1;
elif [ -x "$arg1" ] && file "$arg1" | grep -q 'ELF'; then
   echo
   echo "The '$arg1' file is an ELF binary executable ok for 'ldd' check!!"
else
   echo
   echo "The '$arg1' file is not an ELF binary executable!!"
   echo "Exiting script!"
   echo
   exit 1;
fi

#
# Check the binary file.
#

echo
ldd $arg1 > checklib.out

#
# Verify the 'ldd' results.
#

if [ ! -f checklib.out ]; then
  status=2
else
  cat checklib.out | grep "not found"
  status=$?
fi

#
# $status Values
#
#   0  --> Missing 'shared libraries'.
#   1  --> All 'share libraries' are ok!
#   2  --> Error processing the 'checklib.out' file.
#

if [ $status = 2 ]
 then
 echo
 echo "Unable to verify that the required 'shared libraries' are"
 echo "installed/available on this OS system which allows the binary files"
 echo "to execute."
 echo

 ldd $arg1

 echo
 echo "Exiting with an error!"
 echo
 exit 2;

elif [ $status = 0 ]
 then

 echo
 echo "The 'shared libraries' required to execute the '$arg1' binary"
 echo "file is NOT installed/available on this OS system!"
 echo

 ldd $arg1

 echo
 echo "Exiting with an error!"
 echo
 exit 3;

else

 echo
 echo "The 'shared libraries' required to execute the '$arg1' binary"
 echo "file is installed/available on this OS system!"
 echo

 ldd $arg1

 echo
 echo "Exiting OK!"
 echo
 exit 0;

fi

