package main

import (
	"github.com/vchatchai/myFarm/service/web"

	"github.com/vchatchai/myFarm/service/mqttclient"
	//import the Paho Go MQTT library
)

const TOPIC = "#"

func main() {
	go mqttclient.Listen(TOPIC)
	web.StartWebService()

}
