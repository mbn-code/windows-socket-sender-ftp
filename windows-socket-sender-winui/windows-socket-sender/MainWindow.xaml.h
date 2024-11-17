#pragma once

#include "MainWindow.g.h"

namespace winrt::windows_socket_sender::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        // function definitions for MainWindow.xaml.cpp ---------------------------------------------------------------------------

		void ConnectButtonFTP(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void FileSenderButton(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        // ------------------------------------------------------------------------------------------------------------------------

    };
}

namespace winrt::windows_socket_sender::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
