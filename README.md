# 🚗 Smart Parking System

A sensor-driven parking management system that detects vacant and occupied parking spots using ultrasonic sensors. The system can be extended to include automatic ticketing, fee calculation, and live dashboards for real-time space monitoring.

![Image](https://github.com/user-attachments/assets/eaef02ec-fffa-41df-8416-4c2927655ebc)



---

## 🏗️ System Architecture

    This project presents the design, development, and testing of a smart parking system that:

- Detects the presence of vehicles using ultrasonic sensors

- Communicates status updates via MQTT protocol

- Provides live feedback on a 16x2 LCD screen

- Leverages wireless communication via the ESP32-S3 chip onboard the Arduino R4 Wi-Fi

- Simulates large-scale car park scenarios using AI-generated datasets

- Tested on my driveway with my vehicle: 2014 Hyundai i20, the system demonstrated accurate vehicle detection, robust real-time data transmission, and reliable MQTT connectivity — even under battery-powered conditions.

## ⚙️ Technology used

Hardware:

-  Arduino R4 Wi-Fi with integrated ESP32-S3

- Ultrasonic Sensor (HC-SR04)

- 16x2 LCD Display

Software & Protocols:

- Arduino IDE

- MQTT Protocol (`via MQTT Explorer`)

-  MQTT Client(`via Hive MQ Cloud Cluster`)

## Circuit Diagram for Smart Parking System

![Image](https://github.com/user-attachments/assets/91d2adac-3546-4871-a6bd-0cba6b5689a9)

## 📈 Key Features

✅ Real-time Detection – Detects and displays vehicle presence instantly

✅ Live MQTT Updates – Publishes parking status to an MQTT broker

✅ LCD Feedback Display – Clear, live updates shown on 16x2 LCD

✅ Scalable Design – Tested for single-space and simulated multi-space environments

✅ Portable Setup – Operates reliably on battery power

![Image](https://github.com/user-attachments/assets/44d11abb-913f-4800-b9bb-082f8b2b1a88)

## 🧪 Testing Highlights

✔️ Sensor Accuracy – Consistent distance measurements across test scenarios

✔️ MQTT Reliability – Successful message publishing and system responsiveness

✔️ Scalability – Simulated multi-vehicle environments using AI-generated datasets

![Image](https://github.com/user-attachments/assets/df6f9967-4d4e-4c05-87eb-64850be7e381)

![Image](https://github.com/user-attachments/assets/14b05e47-9b30-4af5-8397-0108c6a938a4)


## 👨‍💻 Code 

![Image](https://github.com/user-attachments/assets/333bd20b-a9fc-4b42-b906-e29255ad4c18)

## 📸 System Demo

![Image](https://github.com/user-attachments/assets/fa1ac3c8-96f2-427d-b663-5e55288bb5f6)

![Image](https://github.com/user-attachments/assets/8f5469ff-df71-4b28-8de7-0cf8b6457e9d)

![Image](https://github.com/user-attachments/assets/f78ac494-a0b0-418f-a8a8-a2eebf233d47)

![Image](https://github.com/user-attachments/assets/c66b731d-1a7e-4e52-896a-3fb33ad7859f)

![Image](https://github.com/user-attachments/assets/09cad1e3-8364-4758-981b-3493482445f2)

![Image](https://github.com/user-attachments/assets/8c15f9ee-6cbc-4dbb-ba6b-e2427eb1b30b)

![Image](https://github.com/user-attachments/assets/daf29936-6fc7-4cb5-a353-cfd8bdc86cdc)

## 🔮 Results

☁️ The driveway parking data I collected with my vehicle indicates a clear transition between occupied and empty states. The vehicle was detected as occupying the parking space from approximately `23:38:06 to 23:39:01` on `24/04/2025`, consistently returning `“occupied”` messages during this period. After `23:39:01`(Highlighted in yellow), the system began returning `“empty”` ({}) messages, indicating the vehicle had left the sensor’s detection range and was no longer parked. The messages continued to show an empty status with consistent time intervals, confirming the reliability and responsiveness of the ultrasonic sensor and MQTT communication over Wi-Fi during the test. 

![Image](https://github.com/user-attachments/assets/1412caac-a89c-421f-a0be-6a175994a63b)

![Image](https://github.com/user-attachments/assets/b319edcf-667e-4714-9d50-022f4d346c95)


## 🔭 Larger scale car park (Generative AI)

To better visualize the potential impact of this system beyond a single use case, I expanded the original data using generative AI to simulate a larger-scale car park as seen in `Figure 31`. This simulation used the same MQTT message patterns observed in the driveway test, extrapolating them across multiple parking bays to mimic the functionality of a smart car park. Each bay in this generated model will be operated similarly to the tested device, continuously publishing occupancy updates to an MQTT broker hosted on HiveMQ Cloud. 

This approach highlights a key advantage of the system, which is scalability. By replicating the original device’s behaviour across multiple bays, it becomes clear how a network of smart parking sensors could function together to monitor multiple vehicles simultaneously in real-time. With HiveMQ Cloud providing a reliable and scalable MQTT infrastructure, this system can handle a larger volume of messages without a drop in performance, making it suitable for use in residential complexes, commercial car parks, or smart city environments. 

![Image](https://github.com/user-attachments/assets/14e12c19-f301-421e-8e72-41a771f7857a)

The AI-generated data simulates a larger, multi-bay car park consisting of 10 parking spaces monitored over a similar timeframe. This extended dataset reflected a more dynamic environment, with different bays being occupied and vacated. It illustrated the potential of the system to handle multiple devices publishing MQTT messages concurrently to the HiveMQ broker cluster, which adopts multiple devices with ease, with no delay or data loss. Compared to the single-bay driveway test conducted on my driveway, the simulated scenario demonstrated how the same architecture could scale effectively, providing real-time monitoring across a larger infrastructure. This comparison reinforces the versatility and scalability of the smart parking system when expanded to commercial or urban environments. 

## ⭐ Star this repo if you like the project!
`Let's make parking smarter and cities less congested 🚙💡`
