package mqttclient

import (
	"fmt"
	"log"
	"net/url"
	"os"
	"regexp"
	"strings"
	"time"

	"github.com/vchatchai/myFarm/service/db"

	mqtt "github.com/eclipse/paho.mqtt.golang"
)

const DEFAULT_MQTT_URL = "localhost"
const DEFAULT_MQTT_PORT = "1883"

var mqtt_url string
var mqtt_port string
var mqtt_uri *url.URL

func init() {
	mqtt_url, ok := os.LookupEnv("MQTT_URL")
	if !ok {
		mqtt_url = DEFAULT_MQTT_URL
	}

	mqtt_port, ok = os.LookupEnv("MQTT_URL")
	if !ok {
		mqtt_port = DEFAULT_MQTT_PORT
	}
	var err error
	mqtt_uri, err = url.Parse(fmt.Sprintf(`tcp://%s:%s`, mqtt_url, mqtt_port))
	if err != nil {
		panic(err)
	}
}

func Connect(clientId string) mqtt.Client {
	opts := createClientOptions(clientId)
	client := mqtt.NewClient(opts)
	token := client.Connect()
	for !token.WaitTimeout(3 * time.Second) {
	}
	if err := token.Error(); err != nil {
		log.Fatal(err)
	}
	return client
}

func createClientOptions(clientId string) *mqtt.ClientOptions {
	opts := mqtt.NewClientOptions()
	opts.AddBroker(fmt.Sprintf("tcp://%s", mqtt_uri.Host))
	opts.SetUsername(mqtt_uri.User.Username())
	password, _ := mqtt_uri.User.Password()
	opts.SetPassword(password)
	opts.SetClientID(clientId)
	return opts
}

func Listen(topic string) {
	client := Connect("sub1")
	client.Subscribe(topic, 0, func(client mqtt.Client, msg mqtt.Message) {
		topic := msg.Topic()
		message := db.Message{
			time.Now(),
			topic,
			getFarmName(topic),
			getType(topic),
			getDeviceID(topic),
			string(msg.Payload()),
		}
		fmt.Printf("* [%s] %s %v\n", msg.Topic(), string(msg.Payload()), message)
		db.Save(message)
	})
}

var farmNameRe = regexp.MustCompile(`^/\w+`)
var deviceIDRe = regexp.MustCompile(`\d+`)
var types = []string{"temperature", "valve", "pump", "humidity"}

func getDeviceID(topic string) string {
	result := deviceIDRe.FindString(topic)
	return result
}

func getType(topic string) string {
	for _, t := range types {
		if strings.Contains(topic, t) {
			return t
		}
	}
	return ""
}

func getFarmName(topic string) string {
	result := farmNameRe.FindString(topic)
	return result
}

func ValveON(topic string) {
	client := Connect("pub")
	client.Publish(topic, 0, false, "on")
}
