#include <Windows.h>
#include <UI.h>
#include <Controls/Button.h>
#include <Controls/Panel.h>
#include <Controls/Label.h>
#include <Controls/PictureBox.h>
#include <Controls/ProgressBar.h>
#include <Controls/Layout/VerticalLayout.h>
#include <Controls/Layout/HorizontalLayout.h>
#include <Controls/Slider.h>
#include <Controls/TextBox.h>
#include <Controls/ComboBox.h>
#include <Controls/CheckBox.h>
#include <Controls/Layout/GridLayout.h>
#include <Controls/Layout/TableLayout.h>
#include <Controls/ToggleSwitch.h>
#include <Controls/TabControl.h>
#include <Events/EventListener.h>
#include <iostream>
#include <Controls/CustomDialogBox.h>

// We use the RanGui namespace to avoid conflicts
using namespace RanGui;

class ToggleSwitchListener : public EventListener
{
public:
    ToggleSwitchListener(ToggleSwitch *toggleSwitch) : m_toggleSwitch(toggleSwitch) {}

    void OnEvent(const Event &event) override
    {
        if (event.GetType() != EventType::MouseMove)
        {
            std::cout << "ToggleSwitch event: " << std::to_string((int)event.GetType()) << std::endl;
        }
        if (event.GetType() == EventType::Click)
        {
            std::cout << "ToggleSwitch clicked: " << m_toggleSwitch->IsChecked() << std::endl;
        }
    }

private:
    ToggleSwitch *m_toggleSwitch;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static UI *ui = nullptr;

    switch (uMsg)
    {
    case WM_CREATE:
    {
        ui = new UI((void **)hwnd);
        ui->Initialize();

        // custom dialog box
        {
            auto dialogBox = std::make_unique<CustomDialogBox>(100.f, 700.f, 400.f, 200.f);
            dialogBox->SetBackgroundColor(ControlColor::White);
            dialogBox->SetTitle(L"Message Box Title");
            dialogBox->SetMessage(L"This is a message inside the message box.");
            dialogBox->EnableWindowMove(true);

            dialogBox->AddButton(L"OK", []()
                                 { std::cout << "OK clicked" << std::endl; });
            dialogBox->AddButton(L"Cancel", []()
                                 { std::cout << "Cancel clicked" << std::endl; });

            ui->GetControlManager()->AddControl(std::move(dialogBox));
        }

        // with layout
        {
            auto panel = std::make_unique<Panel>(50.f, 50.f, 600.f, 500.f);
            panel->SetBackgroundColor(ControlColor::LightBlue); // Change the color of the panel

            auto layout = std::make_unique<VerticalLayout>(100.f, 50.f, 800.f, 500.f, 10.0f); // Set spacing to 10

            auto button = std::make_unique<Button>(L"Apply", 0.f, 0.f, 100.f, 40.f);
            button->SetColor(ControlColor::LightGreen, ControlColor::Green);
            button->SetTextColor(ControlColor::White);
            button->SetTextAlignment(TextAlignment::Center); // Align the text to the center
            // TOOLTIP
            button->SetupTooltip(L"Click me");
            // another type of binding event
            button->AddEventListener(std::make_shared<LambdaEventListener>(EventType::Click, [](const Event &event)
                                                                           {
                if (event.GetType() == EventType::Click)
                {
                    std::cout << "Button clicked" << std::endl;
                } }));

            auto pictureBox = std::make_unique<PictureBox>(L"r.png", 0.f, 0.f, 100.f, 100.f);

            auto progressBar = std::make_unique<ProgressBar>(0.f, 0.f, 280.f, 20.f);
            progressBar->SetProgress(0.9f); // Set initial progress to 60%

            auto linearSlider = std::make_unique<Slider>(0.f, 0.f, 280.f, 20.f);
            linearSlider->SetTrackColor(ControlColor::Blue);
            linearSlider->SetThumbColor(ControlColor::DarkGray);
            linearSlider->SetStyle(SliderStyle::Linear);

            auto circularSlider = std::make_unique<Slider>(0.f, 0.f, 280.f, 20.f);
            circularSlider->SetTrackColor(ControlColor::Blue);
            circularSlider->SetThumbColor(ControlColor::DarkGray);
            linearSlider->SetStyle(SliderStyle::Circular);

            auto inputBox = std::make_unique<TextBox>(0.f, 0.f, 280.f, 30.f);
            inputBox->SetText(L"Type here...");
            inputBox->SetTextColor(ControlColor::Black);
            inputBox->SetBackgroundColor(ControlColor::White);
            inputBox->SetBorderColor(ControlColor::Black);
            // inputBox->SetTextAlignment(TextAlignment::Left);

            auto comboBox = std::make_unique<ComboBox>(0.f, 0.f, 280.f, 30.f);
            comboBox->AddItem(L"Option 1");
            comboBox->AddItem(L"Option 2");
            comboBox->AddItem(L"Option 3");
            comboBox->AddItem(L"Option 4");
            comboBox->AddItem(L"Option 5");
            comboBox->AddItem(L"Option 6");
            comboBox->AddItem(L"Option 7");
            comboBox->SetTextColor(ControlColor::Black);
            comboBox->SetBackgroundColor(ControlColor::White);
            comboBox->SetBorderColor(ControlColor::Black);
            comboBox->SetHoverColor(ControlColor::LightGray);
            comboBox->SetSelectedIndex(0);
            comboBox->SetVisibleItemCount(3); // Show 3 items before scrolling
            comboBox->SetupTooltip(L"Pick one option");

            auto checkBoxLeft = std::make_unique<CheckBox>(L"Accept Terms", 0.f, 0.f, 50.f, 30.f);
            checkBoxLeft->SetTextColor(ControlColor::Black);
            checkBoxLeft->SetBackgroundColor(ControlColor::White);
            checkBoxLeft->SetBorderColor(ControlColor::Black);
            checkBoxLeft->SetCheckColor(ControlColor::Green);
            checkBoxLeft->SetupTooltip(L"Check to accept terms", 0.f, 0.f, 150.f, 30.f);

            auto toggleSwitch1 = std::make_unique<ToggleSwitch>(0.f, 0.f, 50.f, 20.f);
            toggleSwitch1->SetBackgroundColor(ControlColor::LightGray);
            toggleSwitch1->SetBorderColor(ControlColor::Black);
            toggleSwitch1->SetThumbColor(ControlColor::White);
            toggleSwitch1->SetupTooltip(L"Click to toggle", 0.f, 0.f, 150.f, 30.f);

            auto toggleSwitchPtr = toggleSwitch1.get();
            auto toggleSwitchListener = std::make_shared<ToggleSwitchListener>(toggleSwitchPtr);
            toggleSwitch1->AddEventListener(toggleSwitchListener);

            layout->AddControl(std::move(button));
            layout->AddControl(std::move(pictureBox));
            layout->AddControl(std::move(progressBar));
            layout->AddControl(std::move(linearSlider));
            layout->AddControl(std::move(circularSlider));
            layout->AddControl(std::move(inputBox));
            layout->AddControl(std::move(comboBox));
            layout->AddControl(std::move(checkBoxLeft));
            layout->AddControl(std::move(toggleSwitch1));

            panel->SetLayout(std::move(layout));
            ui->GetControlManager()->AddControl(std::move(panel));
        }

        // grid layout
        {
            auto panel = std::make_unique<Panel>(800.f, 50.f, 600.f, 600.f);
            panel->SetBackgroundColor(ControlColor::LightBlue);

            auto gridLayout = std::make_unique<GridLayout>(50.f, 50.f, 500.f, 500.f, 3, 3, 10.0f); // 3x3 grid with spacing 10

            // PictureBox to the grid
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    auto pictureBox = std::make_unique<PictureBox>(L"r.png", 0.f, 0.f, 100.f, 100.f);
                    gridLayout->AddControl(std::move(pictureBox), row, col);
                }
            }

            panel->SetLayout(std::move(gridLayout));
            ui->GetControlManager()->AddControl(std::move(panel));
        }

        // // table layout
        // {
        //     auto panel = std::make_unique<Panel>(50.f, 50.f, 500.f, 500.f);
        //     panel->SetColor(ControlColor::LightBlue);

        //     auto table = std::make_unique<TableLayout>(0.f, 0.f, 500.f, 500.f, 4, 4, 10.0f); // 4x4 table with spacing 10

        //     // Set headers
        //     table->SetHeader(0, L"Header 1");
        //     table->SetHeader(1, L"Header 2");
        //     table->SetHeader(2, L"Header 3");
        //     table->SetHeader(3, L"Header 4");

        //     for (int row = 1; row < 4; ++row)
        //     {
        //         for (int col = 0; col < 4; ++col)
        //         {
        //             auto label = std::make_unique<Label>(L"Item " + std::to_wstring(row) + L"," + std::to_wstring(col), 0.f, 0.f, 100.f, 40.f);
        //             table->SetCell(row, col, std::move(label));
        //         }
        //     }

        //     panel->SetLayout(std::move(table));
        //     ui->GetControlManager()->AddControl(std::move(panel));
        // }

        // no layout
        // {
        //     auto panel = std::make_unique<Panel>(50.f, 50.f, 800.f, 800.f);
        //     panel->SetColor(ControlColor::LightBlue);

        //     auto button = std::make_unique<Button>(L"Apply", 60.f, 60.f, 100.f, 40.f);
        //     button->SetColor(ControlColor::LightGreen, ControlColor::Green);
        //     button->SetTextColor(ControlColor::White);
        //     button->SetFontFamilyName(L"Courier New");
        //     button->SetTextAlignment(TextAlignment::Center);
        //     // button->SetStyle(ButtonStyle::Flat);
        //     panel->AddControl(std::move(button));

        //     auto label = std::make_unique<Label>(L"Settings", 10.f, 10.f);
        //     label->SetColor(ControlColor::White);
        //     panel->AddControl(std::move(label));

        //     auto pictureBox = std::make_unique<PictureBox>(L"r.png", 200.f, 100.f, 200.f, 200.f);
        //     panel->AddControl(std::move(pictureBox));

        //     auto progressBar = std::make_unique<ProgressBar>(100.f, 450.f, 280.f, 20.f);
        //     progressBar->SetProgress(0.5f);
        //     panel->AddControl(std::move(progressBar));

        //     auto slider = std::make_unique<Slider>(0.f, 0.f, 280.f, 20.f);
        //     slider->SetTrackColor(ControlColor::Aqua);
        //     slider->SetThumbColor(ControlColor::DarkGreen);
        //     panel->AddControl(std::move(slider));

        //     auto inputBox = std::make_unique<TextBox>(10.f, 350.f, 280.f, 30.f);
        //     inputBox->SetText(L"Type here...");
        //     // inputBox->SetTextColor(ControlColor::Black);
        //     // inputBox->SetBackgroundColor(ControlColor::White);
        //     // inputBox->SetBorderColor(ControlColor::Black);
        //     panel->AddControl(std::move(inputBox));

        //     auto comboBox = std::make_unique<ComboBox>(300.f, 20.f, 280.f, 30.f);
        //     comboBox->AddItem(L"Option 1");
        //     comboBox->AddItem(L"Option 2");
        //     comboBox->AddItem(L"Option 3");
        //     comboBox->AddItem(L"Option 31");
        //     comboBox->AddItem(L"Option 4");
        //     comboBox->AddItem(L"Option 5");
        //     comboBox->AddItem(L"Option 6");
        //     comboBox->AddItem(L"Option 7");
        //     comboBox->AddItem(L"Option 8");
        //     comboBox->SetTextColor(ControlColor::Black);
        //     comboBox->SetBackgroundColor(ControlColor::White);
        //     comboBox->SetBorderColor(ControlColor::Black);
        //     panel->AddControl(std::move(comboBox));

        //     auto checkBox = std::make_unique<CheckBox>(L"Accept Terms", 460.f, 450.f, 280.f, 30.f);
        //     checkBox->SetTextColor(ControlColor::Black);
        //     checkBox->SetBackgroundColor(ControlColor::White);
        //     checkBox->SetBorderColor(ControlColor::Black);
        //     checkBox->SetCheckColor(ControlColor::Green);
        //     panel->AddControl(std::move(checkBox));

        //     ui->GetControlManager()->AddControl(std::move(panel));
        // }

        // auto panel = std::make_unique<Panel>(50.f, 50.f, 500.f, 500.f);
        // panel->SetColor(ControlColor::LightBlue);

        // auto tabControl = std::make_unique<TabControl>(0.f, 0.f, 500.f, 500.f);

        // auto tabPage1 = std::make_unique<TabPage>(L"Tab 1");
        // auto tabPage2 = std::make_unique<TabPage>(L"Tab 2");
        // auto tabPage3 = std::make_unique<TabPage>(L"Tab 3");

        // auto label1 = std::make_unique<Label>(L"Content for Tab 1", 0.f, 0.f, 400.f, 400.f);
        // auto button = std::make_unique<Button>(L"Button in Tab 2", 0.f, 0.f, 40.f, 30.f);
        // auto label3 = std::make_unique<Label>(L"Content for Tab 3", 0.f, 0.f, 400.f, 400.f);

        // tabPage1->SetContent(std::move(label1));
        // tabPage2->SetContent(std::move(button));
        // tabPage3->SetContent(std::move(label3));

        // tabControl->AddTab(std::move(tabPage1));
        // tabControl->AddTab(std::move(tabPage2));
        // tabControl->AddTab(std::move(tabPage3));

        // panel->AddControl(std::move(tabControl));
        // ui->GetControlManager()->AddControl(std::move(panel));

        return 0;
    }

    case WM_PAINT:
        if (ui)
        {
            ui->Render();
        }
        return 0;
    case WM_SIZE:
        if (ui)
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            ui->OnResize(width, height);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        if (ui)
        {
            ui->ProcessWinProc({hwnd, uMsg, wParam, lParam});
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"UIWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"UIWindowClass",
        L"UI Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}