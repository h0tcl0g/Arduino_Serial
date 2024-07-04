//
//  CustomModifiers.swift
//  20240126
//
//  Created by 柴田大暉 on 2024/05/09.
//

import SwiftUI

struct CustomButtonModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .frame(width: 80, height: 10)
            .padding(20)
            .foregroundColor(.white)
    }
}

struct CustomButtonLabelModifier: ViewModifier {
    func body(content: Content) -> some View {
        content
            .bold()
            .frame(width: 70)
            .padding()
    }
}

extension View {
    func customButtonModifier() -> some View {
        modifier(CustomButtonModifier())
    }
    func customButtonLabalModifier() -> some View {
        modifier(CustomButtonLabelModifier())
    }
}
