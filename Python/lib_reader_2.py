import paho.mqtt.client as mqtt #import the client1
from csv import DictReader
import sys
Found=False                                                                     #bool variable to check if component in library, default false
try:
    Found_Data=sys.argv[1].replace('\n','').split(',') 
except:
    Found_Data=input("input data manually: ").replace('\n','').split(',')
for text in Found_Data:
    IC_Name=text #input("Please enter the IC name: ")                                 #takes text on the IC as input name
    with open("IC_Library.csv", "r") as csv_file:                                   #open IC Library
        IC_Lib=DictReader(csv_file)                                                 #uses csv reader to treat it as a dictionary
        for row in IC_Lib:                                                          #cycles through all rows in the Library
            if row['\ufeffname']==IC_Name:                                             #checks if the name matches the input
                Found=True                                                          #sets found to true if the input matches a name in the library
                pinout=row['pinout'].split("|")                                     #splits pinout in half using marker in the CSV
                sub0_pinout=pinout[0].split(",")                                    #deliminates each half to individual list elements
                sub1_pinout=pinout[1].split(",")
                sub1_pinout.reverse()                                               #reverse the second half to match actual pinout style
                length=(len(sub1_pinout)+len(sub1_pinout))/2                        #checks number of pins and divides by 2, ensures it is actually split in half
                message1=row["\ufeffname"] + ': ' + row["description"]
                message2=row["link to datasheet"]
                message3=sub0_pinout[0]+'\t|--o--| '+sub1_pinout[0]
                for i in range(int(length)):
                    if i!=0:    
                        message3=message3+'\n'+sub0_pinout[i]+'\t|-----| '+sub1_pinout[i]
    if Found==False:                                                                #if found never gets set to true the component is not in the library so reports this to the user
        print("Text Not Found")
print(message1)
print(message2)
print(message3)
broker_address="test.mosquitto.org" 
client = mqtt.Client("P1") #create new instance
client.connect(broker_address) #connect to broker
client.publish("immersive_headset_demo",message1)#publish
client.publish("immersive_headset_demo",message2)#publish
client.publish("immersive_headset_demo",message3)#publish
