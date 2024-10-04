import requests
import keyboard
import csv



def declare_pose():
    wifi_address = 'http://192.168.4.22'

    fields = ['roll', 'pitch', 'thumb', 'pointer', 'middle', 'ax', 'ay', 'az', 'sign']
    filename = "data.csv"
    with open(filename, 'a') as csvfile:
        # creating a csv dict writer object
        writer = csv.writer(csvfile)
        #writer.writerow(fields)
        while(1):
            print("what hang sign is this?")
            y = {"sign":input()}

            if y['sign'] == 'q':
                break

            key = ""
            while key != "q":
                key = keyboard.read_key()
                # if r pressed, record samples
                if key == "r":
                    print("recording...")
                    r = requests.get(wifi_address).json()
                    r.update(y)
                    r_vals=r.values()

                    writer.writerow(r_vals)
                    print("added rows")

                





if __name__ == '__main__':
    declare_pose()
   