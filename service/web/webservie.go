package web

import (
	"net/http"

	"github.com/gorilla/mux"
)

const (
	CONN_HOST = "localhost"
	CONN_PORT = "8080"
)

func StartWebService() {
	router := mux.NewRouter()

	err := http.ListenAndServe(CONN_HOST+":"+CONN_PORT, router)
	if err != nil {
		panic(err)
	}
}

func ValveOn() {

}
