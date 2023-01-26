import subprocess
try:
     #subprocess.call(r'OCR.bat')                                               # runs the OCR.bat file, is commented out for testing purposes
     file_name = "gcloudRead.txt"
     file_read = open(file_name, "r")                                    # opening and reading the file 
     text = '"text":'                                                           # asking the user to enter the string to be searched
     lines = file_read.readlines()                                              # reading file content line by line.
     new_list = []
     idx = 0
     for line in lines:                                                         # looping through each line in the file
          if text in line:                                                      # if line have the input string, get the index of that 
               new_list.insert(idx, line)                                            #line and put the line into newly created list 
               idx += 1
          file_read.close()                                                     # closing file after reading
     if len(new_list)==0:                                                       # if length of new list is 0 that means the input string doesn't found in the text file
          print("\n\"" +text+ "\" is not found in \"" +file_name+ "\"!")
     else:
          foundText = new_list[len(new_list)-1]                                 # displaying the lines containing given string
          foundText = foundText[17:]
          foundText = foundText.replace('\\n',',')
          foundText = foundText.replace('"','')
          print(foundText)
          subprocess.run(['python','IC_LIB_READER.py',foundText])    

except :                                                                        # entering except block if input file doesn't exist 
    print("\nThe file doesn't exist!")