//
//  ContentView.swift
//  20240126
//
//  Created by 柴田大暉 on 2024/01/26.
//

import SwiftUI
import Network

struct ContentView: View {
    @State var host: NWEndpoint.Host = "192.168.36.31"    //Receiver's IP
    @State var port: NWEndpoint.Port = 12345
    @State var connection: NWConnection?
    @State var movSpeed: Int = 1
    
    var body: some View {
        ZStack {
            Color(red: 0.99, green: 0.99, blue: 0.99)
                .ignoresSafeArea()
            
            VStack {
                
                Spacer()
                
                VStack {
                    Text("動作速度")
                        .scaleEffect(2)
                        .padding(30)
                    
                    Button {
                        movSpeed += 1
                        if (movSpeed > 10) {
                            movSpeed = 10
                        }
                        send("\(movSpeed)".data(using: .utf8)!)
                    } label: {
                        Image(systemName: "triangle.fill")
                            .foregroundColor(movSpeed >= 10 ? .gray.opacity(0) : .gray)
                            .scaleEffect(1.5)
                    }
                    
                    Text(String(movSpeed))
                        .scaleEffect(2)
                        .padding()
                    
                    Button {
                        movSpeed -= 1
                        if (movSpeed < 1) {
                            movSpeed = 1
                        }
                        send("\(movSpeed)".data(using: .utf8)!)
                    } label: {
                        Image(systemName: "triangle.fill")
                            .foregroundColor(movSpeed <= 1 ? .gray.opacity(0) : .gray)
                            .rotationEffect(Angle(degrees: 180))
                            .scaleEffect(1.5)
                    }
                }
                
                Spacer()
                
                
                HStack(spacing: 10) {
                    Button {
                        connect()
                    } label: {
                        Text("Connect")
                            .customButtonLabalModifier()
                    }
                    .customButtonModifier()
                    .background(LinearGradient(colors: [.blue, Color(red: 0, green: 0, blue: 1, opacity: 0.7)], startPoint: .topLeading, endPoint: .bottomLeading), in: RoundedRectangle(cornerRadius: 15))
                    .shadow(radius: 5)
                    
                    Button {
                        send("reset".data(using: .utf8)!)
                    } label: {
                        Text("Reset")
                            .customButtonLabalModifier()
                    }
                    .customButtonModifier()
                    .background(LinearGradient(colors: [Color(red: 0, green: 1, blue: 0, opacity: 0.5), .green], startPoint: .topLeading, endPoint: .bottomTrailing), in: RoundedRectangle(cornerRadius: 15))
                    .shadow(radius: 5)
                    
                    Button {
                        send("quit".data(using: .utf8)!)
                    } label: {
                        Text("Quit")
                            .customButtonLabalModifier()
                    }
                    .customButtonModifier()
                    .background(LinearGradient(colors: [Color(red: 1, green: 0, blue: 0, opacity: 0.5), .red], startPoint: .topLeading, endPoint: .bottomTrailing), in: RoundedRectangle(cornerRadius: 15))
                    .shadow(radius: 5)
                }
                .frame(minWidth: 300)
            }
        }
    }
    
    func send(_ payload: Data) {
        connection!.send(content: payload, completion: .contentProcessed({ sendError in}))
    }
    
    func connect() {
        connection = NWConnection(host: host, port: port, using: .udp)
        connection!.start(queue: .global())
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
