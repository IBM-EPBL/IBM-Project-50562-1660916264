from wiotp.sdk import device
import threading
import time

def get_gpsConfig(deviceId):
  gpsConfig = {
      'identity' : {
          'orgId': 'f336wj',
          'typeId': 'GPS',
          'deviceId': deviceId
      },
      'auth': {
          'token': '12345678'
      }
  }
  return gpsConfig

#connect to all 3 devices
client1 = device.DeviceClient(get_gpsConfig('GPS123'))
client1.connect()
client2 = device.DeviceClient(get_gpsConfig('GPS124'))
client2.connect()
client3 = device.DeviceClient(get_gpsConfig('GPS125'))
client3.connect()

#Locations of 3 stations
lat_chn = 13.0827
long_chn = 80.2707

lat_blr=12.97
long_blr=77.56

lat_hyd=17.39
long_hyd=78.46

def send_lat_long(train_name, lat1,long1,lat2,long2,client):
   dir = (lat2-lat1)/abs(lat2-lat1)
   while abs(lat2 - lat1) > 0:
     send_data(train_name,lat1,long1,client)
     lat1  += dir*0.01
     long1 += dir*0.01
     time.sleep(1)

def send_data(train_name, lat1, long1,client):
   location = { 'name': train_name, 'lat': lat1, 'lon': long1, 'icon' : "train", 'iconColor':"black"}
   client.publishEvent(eventId="status", msgFormat="json", data=location, qos=0)

if __name__ =="__main__":
    # creating threads 
    t1 = threading.Thread(target=send_lat_long, args=("Chennai express",lat_chn,long_chn,lat_blr,long_blr,client1))
    t2 = threading.Thread(target=send_lat_long, args=("Charminar express",lat_hyd,long_hyd,lat_chn,long_chn,client2))
    t3 = threading.Thread(target=send_lat_long, args=("Bangalore express",lat_blr,long_blr,lat_hyd,long_hyd,client3))

    #starting all the 3 threads which simulates the 3 trains in transit
    t1.start()
    t2.start()
    t3.start()
 
    # joining the threads and waitig for their execution
    t1.join()
    t2.join()
    t3.join()

