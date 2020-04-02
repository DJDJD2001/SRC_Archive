#include <ESP8266WiFi.h>
#include <Servo.h>

Servo myservo;
WiFiServer server(80);
 
String readString = ""; //建立一个字符串对象用来接收存放来自客户的数据
int myangel = 0;
//响应头
String responseHeaders =
    String("") +
    "HTTP/1.1 200 OK\r\n" +
    "Content-Type: text/html\r\n" +
    "Connection: close\r\n" +
    "\r\n";
 
//网页
String myhtmlPage =
    String("") +
"<html>\n" +
"\n" +
"<head>\n" +
"    <title>ESP8266 Web Server Test</title>\n" +
"    <script defer=\"defer\">\n" +
"        function ledSwitch(n) {\n" +
"            var xmlhttp;\n" +
"            if (window.XMLHttpRequest) {\n" +
"                xmlhttp = new XMLHttpRequest();\n" +
"            } else {\n" +
"                xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n" +
"            }\n" +
"            xmlhttp.onreadystatechange = function () {\n" +
"                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\n" +
"                    document.getElementById(\"txtState\").innerHTML = xmlhttp.responseText;\n" +
"                }\n" +
"            };\n" +
"            if (n == 1) {\n" +
"                xmlhttp.open(\"GET\", \"Switch1\", true);\n" +
"            } else if(n == 2) {\n" +
"                xmlhttp.open(\"GET\", \"Switch2\", true);\n" +
"            } else if(n == 3) {\n" +
"                xmlhttp.open(\"GET\", \"Switch3\", true);\n" +
"            } else if(n == 4) {\n" +
"                xmlhttp.open(\"GET\", \"Switch4\", true);\n" +
"            } else if(n == 5) {\n" +
"                xmlhttp.open(\"GET\", \"Switch5\", true);\n" +
"            }else {\n" +
"                xmlhttp.open(\"GET\", \"Switch6\", true);\n" +
"            }\n" +
"            xmlhttp.send();\n" +
"        }\n" +
"        var lock1 = 0;\n" +
"        var lock2 = 0;\n" +
"        var lock3 = 0;\n" +
"        var lock4 = 0;\n" +
"        var lock5 = 0;\n" +
"        var lock6 = 0;\n" +
"\n" +
"        document.onkeydown = function (event) {\n" +
"                event = event || window.event;\n" +
"                var xmlhttp;\n" +
"                if (window.XMLHttpRequest) {\n" +
"                    xmlhttp = new XMLHttpRequest();\n" +
"                } else {\n" +
"                    xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n" +
"                }\n" +
"                xmlhttp.onreadystatechange = function () {\n" +
"                    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\n" +
"                        document.getElementById(\"txtState\").innerHTML = xmlhttp.responseText;\n" +
"                    }\n" +
"                };\n" +
"                switch (event.keyCode){\n" +
"                    case 37:\n" +
"                        if(lock2 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch2\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock2 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                    case 38:\n" +
"                        if(lock1 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch1\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock1 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                    case 39:\n" +
"                    if(lock3 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch3\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock3 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                    case 40:\n" +
"                    if(lock4 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch4\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock4 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                    case 88:\n" +
"                    if(lock5 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch5\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock5 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                    case 90:\n" +
"                    if(lock6 == 0){\n" +
"                        xmlhttp.open(\"GET\", \"Switch6\", true);\n" +
"                        xmlhttp.send();\n" +
"                        lock6 = 1;\n" +
"                        }\n" +
"                        break;\n" +
"                }   \n" +
"        }\n" +
"        document.onkeyup = function (event) {\n" +
"                event = event || window.event; \n" +
"                console.log(event.keyCode);\n" +
"                var xmlhttp;\n" +
"                if (window.XMLHttpRequest) {\n" +
"                    xmlhttp = new XMLHttpRequest();\n" +
"                } else {\n" +
"                    xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n" +
"                }\n" +
"                xmlhttp.onreadystatechange = function () {\n" +
"                    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\n" +
"                        document.getElementById(\"txtState\").innerHTML = xmlhttp.responseText;\n" +
"                    }\n" +
"                };\n" +
"                lock1 = 0;\n" +
"                lock2 = 0;\n" +
"                lock3 = 0;\n" +
"                lock4 = 0;\n" +
"                lock5 = 0;\n" +
"                lock6 = 0;\n" +
"                xmlhttp.open(\"GET\", \"Stop\", true);\n" +
"                xmlhttp.send();\n" +
"        }\n" +
"        function Stop() {\n" +
"            var xmlhttp;\n" +
"            if (window.XMLHttpRequest) {\n" +
"                xmlhttp = new XMLHttpRequest();\n" +
"            } else {\n" +
"                xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n" +
"            }\n" +
"            xmlhttp.onreadystatechange = function () {\n" +
"                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\n" +
"                    document.getElementById(\"txtState\").innerHTML = xmlhttp.responseText;\n" +
"                }\n" +
"            };\n" +
"            xmlhttp.open(\"GET\", \"Stop\", true);\n" +
"            xmlhttp.send();\n" +
"        }\n" +
"    </script>\n" +
"</head>\n" +
"<body>\n" +
"    <div id=\"txtState\" style.overflow=\"hidden\"> The robot car competition</div> \n" +
"    <input class=\"b1\" type=\"button\" value=\"Front\" onmousedown=\"ledSwitch(1)\", onmouseup=\"Stop()\"> <br> \n" +
"    <input class=\"b2\" type=\"button\" value=\"Left\" onmousedown=\"ledSwitch(2)\", onmouseup= \"Stop()\"> \n" +
"    <input class=\"b3\" type=\"button\" value=\"Right \" onmousedown=\"ledSwitch(3)\", onmouseup= \"Stop()\"> \n" +
"    <input class=\"u1\" type=\"button\" value=\"Up(z)\" onmousedown=\"ledSwitch(4)\", onmouseup= \"Stop()\"> \n" +
"    <input class=\"u2\" type=\"button\" value=\"Down(x)\" onmousedown=\"ledSwitch(5)\", onmouseup= \"Stop()\"> <br> \n" +
"    <input class=\"b4\" type=\"button\" value=\"Back\" onmousedown=\"ledSwitch(6)\", onmouseup= \"Stop()\">\n" +
"    <style>\n" +
"        .b1 {\n" +
"            background-color: #4CAF50;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 10px 50px 0px 120px;\n" +
"        }\n" +
"        .b2 {\n" +
"            background-color: cornflowerblue;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 0px 50px 0px 0px;\n" +
"        }\n" +
"        .b3 {\n" +
"            background-color: darkgoldenrod;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 0px 50px 0px 100px;\n" +
"        }\n" +
"        .u1 {\n" +
"            background-color: cornflowerblue;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 0px 50px 0px 50px;\n" +
"        }\n" +
"        .u2 {\n" +
"            background-color: darkgoldenrod;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 0px 50px 0px 50px;\n" +
"        }\n" +
"        .b4 {\n" +
"            background-color: orangered;\n" +
"            /* Green */\n" +
"            font-size: 20px;\n" +
"            border: none;\n" +
"            color: white;\n" +
"            padding: 30px 32px;\n" +
"            text-align: center;\n" +
"            margin: 0px 50px 0px 120px;\n" +
"        }\n" +
"    </style>\n" +
"</body>\n" +
"</html>";





void setup() {
  Serial.begin ( 115200 );
  Serial.println("dddddddd!");
  // 设置内网
  IPAddress softLocal(192,168,128,1);   // 1 设置内网WIFI IP地址
  IPAddress softGateway(192,168,128,1);
  IPAddress softSubnet(255,255,255,0);
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
   
  String apName = ("ZUDZX"+(String)ESP.getChipId());  // 2 设置WIFI名称
  const char *softAPName = apName.c_str();
   
  WiFi.softAP(softAPName, "299792458");      // 3创建wifi  名称 +密码 adminadmin
   
  IPAddress myIP = WiFi.softAPIP();  // 4输出创建的WIFI IP地址
  Serial.print("AP IP address: ");     
  Serial.println(myIP);
   
  Serial.print("softAPName: ");  // 5输出WIFI 名称
  Serial.println(apName);

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.softAPIP().toString().c_str());
  
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);
  myservo.attach(2);
  myservo.write(myangel);
}

bool servo_control = 0;

void loop() {

   
  
  WiFiClient client = server.available(); //尝试建立客户对象
  if (client)                             //如果当前有客户可用
  {
        boolean currentLineIsBlank = true;
        Serial.println("[Client connected]");
 
        while (client.connected()) //如果客户端建立连接
        {
            if (client.available()) //等待有可读数据
            {
                char c = client.read(); //读取一字节数据
                readString += c;        //拼接数据
                /************************************************/
                if (c == '\n' && currentLineIsBlank) //等待请求头接收完成(接收到空行)
                {
                    //比较接收到的请求数据
                    if (readString.startsWith("GET / HTTP/1.1")) //如果是网页请求
                    {
                        client.print(responseHeaders); //向客户端输出网页响应
                        client.print(myhtmlPage);      //向客户端输出网页内容
                        client.print("\r\n");
                    }
                    else if (readString.startsWith("GET /Switch1")) //如果是改变LED状态请求
                    {
                            digitalWrite(5, 1); // 点亮LED
                            digitalWrite(4, 0);// 熄灭LED
                            digitalWrite(12, 1);
                            digitalWrite(14, 0);
                            client.print("Move forward");
                            
                    }
                    else if (readString.startsWith("GET /Switch2")) //如果是改变LED状态请求
                    {
                            digitalWrite(5, 0); // 点亮LED
                            digitalWrite(4, 1);// 熄灭LED
                            digitalWrite(12, 1);
                            digitalWrite(14, 0);
                            client.print("Move left");
                    }
                    else if (readString.startsWith("GET /Switch3")) //如果是改变LED状态请求
                    {
                            digitalWrite(5, 1); // 点亮LED
                            digitalWrite(4, 0);// 熄灭LED
                            digitalWrite(12, 0);
                            digitalWrite(14, 1);
                            client.print("Move right");
                    }
                                      
                    else if (readString.startsWith("GET /Switch4")) //如果是改变LED状态请求
                    {
                            digitalWrite(5, 0); // 点亮LED
                            digitalWrite(4, 1);// 熄灭LED
                            digitalWrite(12, 0);
                            digitalWrite(14, 1);
                            client.print("Move backward");
                    }
                    else if (readString.startsWith("GET /Switch5")) //如果是改变LED状态请求
                    {
                            servo_control = 1;
                            
                            
                            if( myangel < 170)
                            {
                              myangel = myangel + 5;
                              myservo.write(myangel);
                            } 
                            client.print("Angel ++: " + String(myangel));

                    }
                    else if (readString.startsWith("GET /Switch6")) //如果是改变LED状态请求
                    {
                            servo_control = 2;  
                            if(servo_control == 2 && myangel > 10)
                              {
                                myangel = myangel - 5;
                                myservo.write(myangel);    
                              }
                            client.print("Angel --"+ String(myangel));
                    }
                    else if (readString.startsWith("GET /Stop")) //如果是改变LED状态请求
                    {
                            servo_control = 0;
                            digitalWrite(5, 0); // 点亮LED
                            digitalWrite(4, 0);// 熄灭LED
                            digitalWrite(12, 0);
                            digitalWrite(14, 0);
                            client.print("Stop");
                    }
                    else
                    {
                            client.print("\r\n");
                    }
                    break;
                }
 
                if (c == '\n')
                {
                    currentLineIsBlank = true; //开始新行
                }
                else if (c != '\r')
                {
                    currentLineIsBlank = false; //正在接收某行中
                }
                /************************************************/
            }
        }
        delay(1);      //等待客户完成接收
        client.stop(); //结束当前连接:
        Serial.println("[Client disconnected]");
        
        Serial.println(readString); //打印输出来自客户的数据
        readString = "";
    }
}
