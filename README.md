# Hydra

Hydra is a multi-language API that defines **CRUD** operations to containerized micro-services. 

## The vision

1. Hydra will hopefully eventually contain support for all popular languages. 
2. Using Hydra will run a client-server model where servers control but server-server interaction is possible (situations where both micro-services are producers and consumers), but will need to be managed by client code. 
3. Data can be transferred accross application boundries and command and controll can be sent from any hyrda supported container

## Why

Lots of very interesting and useful functionality is language restricted. Instead of needing to re-invent the wheel or port existing code from another language Hydra will enable much easier to develop and maintain multi-language applications.

# Methodologies

It is still early days, this project might go no-where so the direction might pivot but for now here is the proposed novel mechanism.

## Pipes

Most operating systems implement pipes in some way. Linux OS allows the easy construction and use of _named pipes_. These are _first-in-first-out_ os level data structures that can be used to quickly write data. Applications can asynchronously read and write from these pipes. 

### Example

Consider a Server application and 2 client applications. Servers will be created first and open up a command and control channel/pipe. The next client will then spin up. A Hydra component designed for that language will request a pipe for that micro-service which it guarantees only it will read. The service will spin up a new pipe, put it in the mounted volume and then push listen on the channel for any requests. It can also be used as a "fire hose" to just dump data, this will work if the application is expecting continuous data. The server should open this connection on a seperate thread. The next client will then repeat the same process

### Psuedocode

This is pretty much the end goal of what i want people to be able to do.

**CLIENT**
```python
import hydra
connection = hydra.request_connection(hydra.connectionType.CRUD)
connection.get("/controller/action")

packet = {
    someValue="1",
    someOtherValue=1
}

connection.post("/controller/action", data=packet)
```

**SERVER**
```c#
using hydra;
using hydra.connectionTypes;

[HydraController("/controller")]
public class HydraProducer {
    
    [HydraGet("/action")]
    public int times2(){
        return 1;
    }

    [HydraPost("/action")]
    public int times2(Json j) {
        return j.someOtherValue * 2;
    }
    
}

public static void main(string[] args) {
    HydraProducer producer;
    HydraConnection connection = hydra.createCrudSever(producer);
    connection.open();
}


```

## Sockets

The other way which is slightly less desirable is to take advantage of the existing single network capability of docker. Spawning all applications under the same network will allow requests to ports. I don't want to do this for 2 reasons:

1. We will need to implement http servers and clients for each language just to communicate internally within one application. Potentially blocking other ports for useful functionality.
2. I want to create a non-networked solution. Pipes are quick and don't need to utilise the internet protocol stack.

However, this is a good fallback if we find that cross OS compatibility is difficult, which I expect.