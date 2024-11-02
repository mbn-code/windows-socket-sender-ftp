#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::windows_socket_sender::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    #include <winrt/Windows.Networking.Sockets.h>
    #include <winrt/Windows.Storage.Streams.h>

    void MainWindow::btnSend_Click(IInspectable const&, RoutedEventArgs const&)
    {
        btnSend().Content(box_value(L"Sending"));

        // Create a TCP socket and connect to the server
        winrt::Windows::Networking::Sockets::StreamSocket socket;
        winrt::Windows::Foundation::Uri serverUri(L"your_server_address_here");
        socket.ConnectAsync(serverUri, L"your_port_here").Completed([this](auto const&, auto const&)
        {
            // Send data to the server
            winrt::Windows::Storage::Streams::DataWriter writer(socket.OutputStream());
            writer.WriteString(L"Your data here");
            writer.StoreAsync().Completed([this](auto const&, auto const&)
            {
                // Update the button content to "Sent" after sending data
                btnSend().Content(box_value(L"Sent"));
            });
        });
    }


    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        // myButton().Content(box_value(L"Clicked"));
    }
}
