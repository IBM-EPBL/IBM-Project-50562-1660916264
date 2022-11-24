import cv2
import time
import pyzbar.pyzbar as pz
from ibmcloudant.cloudant_v1 import CloudantV1 
from ibm_cloud_sdk_core.authenticators import BasicAuthenticator

authenticator = BasicAuthenticator ('apikey-v2-157db41pwa7immzmyhhr9ezh7ll4nql1q2gbcdn9xcnk', '3620d13725bc37d50ff9e9d9bf5d4b73')
service = CloudantV1(authenticator=authenticator)
service.set_service_url ('https://apikey-v2-157db41pwa7immzmyhhr9ezh7ll4nql1q2gbcdn9xcnk:3620d13725bc37d50ff9e9d9bf5d4b73@994dc686-4910-4586-b44f-0b06c6953c31-bluemix.cloudantnosqldb.appdomain.cloud')

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_PLAIN

while True:
	_, frame = cap.read()
	decodedObjects = pz.decode(frame)
	for obj in decodedObjects:
		a=obj.data.decode('UTF-8') 
		cv2.putText(frame,"Ticket", (50, 50), font, 2,(255,0, 0), 3)
		try:
			response = service.get_document(db='sp45_db', doc_id=a).get_result()
			print(response)
			time.sleep (5)
		except Exception as e:
			print ("Not a Valid Ticket")
			time.sleep (5)
	cv2.imshow ("Frame", frame)
	if cv2.waitKey (1) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()
service.disconnect()