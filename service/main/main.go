package main

import (
	"github.com/vchatchai/myFarm/service/web"

	"github.com/vchatchai/myFarm/service/mqttclient"
	//import the Paho Go MQTT library
)

func main() {
	go mqttclient.ListenAnyMessage()
	go mqttclient.ListenPushButtonMessage()
	web.StartWebService()

}
