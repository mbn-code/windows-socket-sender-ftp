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

    void MainWindow::FileSenderButton(IInspectable const&, RoutedEventArgs const&)
    {
		sendButton().Content(box_value(L"Sending.."));

		// if ftp is done sending and has sent via TCP make the button say "Sent"

    }

	void MainWindow::ConnectButtonFTP(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		connectButton().Content(box_value(L"Connecting.."));

    	// if TCP connection is successful make the button say "Connected" else "Failed" together with error message
		if (true)
		{
			connectButton().Content(box_value(L"Connected"));
		}
		else
		{
			connectButton().Content(box_value(L"Failed"));
		}


	}
}
