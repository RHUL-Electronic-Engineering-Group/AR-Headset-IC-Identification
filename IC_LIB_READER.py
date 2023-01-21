from csv import DictReader

IC_Name=input("Please enter the IC name: ")                                     #takes text on the IC as input name
with open("IC_Library.csv", "r") as csv_file:                                   #open IC Library
    IC_Lib=DictReader(csv_file)                                                 #uses csv reader to treat it as a dictionary
    for row in IC_Lib:                                                          #cycles through all rows in the Library
        if row['ï»¿name']==IC_Name:                                             #checks if the name matches the input
            print(row["ï»¿name"],':',row["description"])                        #outputs name and description
            print(row["link to datasheet"])                                     #provides link to datasheet
            pinout=row['pinout'].split("|")                                     #splits pinout in half using marker in the CSV
            sub0_pinout=pinout[0].split(",")                                    #deliminates each half to individual list elements
            sub1_pinout=pinout[1].split(",")
            sub1_pinout.reverse()                                               #reverse the second half to match actual pinout style
            length=(len(sub1_pinout)+len(sub1_pinout))/2                        #checks number of pins and divides by 2, ensures it is actually split in half
            for i in range(int(length)):
                if i==0: print(sub0_pinout[i],'\t|--o--|',sub1_pinout[i])       #prints first pinout with a marker at the top like a real IC
                else:    print(sub0_pinout[i],'\t|-----|',sub1_pinout[i])       #prints the rest of the pinout as it would be for the IC