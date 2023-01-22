try:
     
     # opening and reading the file 
     file_read = open("gcloudRead.txt", "r")
     
     # asking the user to enter the string to be 
     # searched
     text = '"text":'
     
     # reading file content line by line.
     lines = file_read.readlines()
     
     new_list = []
     idx = 0
     
     # looping through each line in the file
     for line in lines:
               
          # if line have the input string, get the index 
          # of that line and put the
          # line into newly created list 
          if text in line:
               new_list.insert(idx, line)
               idx += 1
     
     # closing file after reading
     file_read.close()
     
     # if length of new list is 0 that means 
     # the input string doesn't
     # found in the text file
     if len(new_list)==0:
          print("\n\"" +text+ "\" is not found in \"" +file_name+ "\"!")
     else:
     
          # displaying the lines 
          # containing given string
          foundText = new_list[len(new_list)-1]
          foundText = foundText[17:]
          foundText = foundText.replace('\\n',',')
          foundText = foundText.replace('"','')

          print(foundText)

# entering except block
# if input file doesn't exist 
except :
    print("\nThe file doesn't exist!")