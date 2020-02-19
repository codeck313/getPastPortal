#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>

const char *ssid = "ASTRA";
const char *password = "astra123";
static const char *LOCATION = "Location";
static const char *SET_COOKIE = "Set-Cookie";
static const char *HEADER_NAMES[] = {LOCATION, SET_COOKIE};
const char *username = "";
const char *password = "";
String portalLocation = "";
WiFiClient client;

void setup()
{

    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {

        delay(1000);
        Serial.print("Connecting..");
    }
}

String portalIP(String ip)
{
    HTTPClient http; //Declare an object of class HTTPClient

    http.begin(ip); //Specify request destination
    http.collectHeaders(HEADER_NAMES, 2);
    int httpCode = http.GET(); //Send the request
    Serial.println(httpCode);
    if (httpCode > 0)
    { //Check the returning code

        String incoming = http.getString(); //Get the request response payload
        portalLocation = http.header(LOCATION);
        Serial.println(incoming); //Print the response payload
        Serial.println("#######################");
        Serial.println(portalLocation);
        return portalLocation;
    }

    http.end(); //Close connection
}

void getPortal(String url)
{
    HTTPClient http;
    http.begin(url);
    // int httpCode = http.GET(); //Send the request
    // Serial.println(httpCode);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("X-Requested-With", "XMLHttpRequest");
    http.addHeader("Content-Length", "71");
    http.addHeader("Origin", "http://172.16.0.2:8090");
    // if (httpCode > 0)
    // { //Check the returning code
    http.POST("mode=191&username="+useraname+"&password="+password+"&a=1581937216630&producttype=0");
    String payload = http.getString(); //Get the response payload
    Serial.println(payload);
    http.end();
    // }
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED)
    { //Check WiFi connection status
        // portalLocation = portalIP("http://192.168.100.1");
        // getPortal("http://172.16.0.2:8090/httpclient.html");
        getPortal("http://172.16.0.2:8090/login.xml");
        getPortal("http://www.google.com");
    }

    delay(30000); //Send a request every 30 seconds
}
