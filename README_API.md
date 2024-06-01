# API Documentation
This is just a basic overview of the API. For more detailed information, please refer to the source code.

## UI Class

### Methods

- `UI(void **hwnd)`: Constructor. Initializes the UI system.
- `void Initialize()`: Initializes UI components.
- `void Render()`: Renders the UI components.
- `void OnResize(UINT width, UINT height)`: Resizes the UI components.
- `ControlManager* GetControlManager()`: Returns the control manager.

## ControlManager Class

### Methods

- `void AddControl(std::unique_ptr<Control> control)`: Adds a control to the manager.

## Control Class

Base class for all UI controls.

## Panel Class

Inherits from `Control`.

### Methods

- `Panel(float x, float y, float width, float height)`: Constructor.
- `void SetColor(D2D1::ColorF color)`: Sets the panel color.
- `void AddControl(std::unique_ptr<Control> control)`: Adds a control to the panel.
- `void SetLayout(std::unique_ptr<Layout> layout)`: Sets the layout for the panel.

## Button Class

Inherits from `Control`.

### Methods

- `Button(const std::wstring& text, float x, float y, float width, float height)`: Constructor.
- `void SetColor(D2D1::ColorF normalColor, D2D1::ColorF hoverColor)`: Sets the button colors.
- `void SetTextColor(D2D1::ColorF color)`: Sets the text color.
- `void SetTextAlignment(TextAlignment alignment)`: Sets the text alignment.

## Label Class

Inherits from `Control`.

### Methods

- `Label(const std::wstring& text, float x, float y)`: Constructor.
- `void SetColor(D2D1::ColorF color)`: Sets the label color.

## PictureBox Class

Inherits from `Control`.

### Methods

- `PictureBox(const std::wstring& imagePath, float x, float y, float width, float height)`: Constructor.

## ProgressBar Class

Inherits from `Control`.

### Methods

- `ProgressBar(float x, float y, float width, float height)`: Constructor.
- `void SetProgress(float progress)`: Sets the progress value (0.0 to 1.0).

## Slider Class

Inherits from `Control`.

### Methods

- `Slider(float x, float y, float width, float height)`: Constructor.
- `void SetTrackColor(D2D1::ColorF color)`: Sets the track color.
- `void SetThumbColor(D2D1::ColorF color)`: Sets the thumb color.
- `void SetStyle(SliderStyle style)`: Sets the slider style (Linear or Circular).

## TextBox Class

Inherits from `Control`.

### Methods

- `TextBox(float x, float y, float width, float height)`: Constructor.
- `void SetText(const std::wstring& text)`: Sets the text.
- `void SetTextColor(D2D1::ColorF color)`: Sets the text color.
- `void SetBackgroundColor(D2D1::ColorF color)`: Sets the background color.
- `void SetBorderColor(D2D1::ColorF color)`: Sets the border color.

## ComboBox Class

Inherits from `Control`.

### Methods

- `ComboBox(float x, float y, float width, float height)`: Constructor.
- `void AddItem(const std::wstring& item)`: Adds an item to the combo box.
- `void SetTextColor(D2D1::ColorF color)`: Sets the text color.
- `void SetBackgroundColor(D2D1::ColorF color)`: Sets the background color.
- `void SetBorderColor(D2D1::ColorF color)`: Sets the border color.
- `void SetHoverColor(D2D1::ColorF color)`: Sets the hover color.
- `void SetSelectedIndex(int index)`: Sets the selected item index.
- `void SetVisibleItemCount(int count)`: Sets the number of visible items before scrolling.

## CheckBox Class

Inherits from `Control`.

### Methods

- `CheckBox(const std::wstring& text, float x, float y, float width, float height)`: Constructor.
- `void SetTextColor(D2D1::ColorF color)`: Sets the text color.
- `void SetBackgroundColor(D2D1::ColorF color)`: Sets the background color.
- `void SetBorderColor(D2D1::ColorF color)`: Sets the border color.
- `void SetCheckColor(D2D1::ColorF color)`: Sets the check color.

## ToggleSwitch Class

Inherits from `Control`.

### Methods

- `ToggleSwitch(float x, float y, float width, float height)`: Constructor.
- `void SetBackgroundColor(D2D1::ColorF color)`: Sets the background color.
- `void SetBorderColor(D2D1::ColorF color)`: Sets the border color.
- `void SetThumbColor(D2D1::ColorF color)`: Sets the thumb color.
- `void AddEventListener(std::shared_ptr<EventListener> listener)`: Adds an event listener.

## VerticalLayout Class

Inherits from `Layout`.

### Methods

- `VerticalLayout(float x, float y, float width, float height, float spacing)`: Constructor.
- `void AddControl(std::unique_ptr<Control> control)`: Adds a control to the layout.

## HorizontalLayout Class

Inherits from `Layout`.

### Methods

- `HorizontalLayout(float x, float y, float width, float height, float spacing)`: Constructor.
- `void AddControl(std::unique_ptr<Control> control)`: Adds a control to the layout.

## GridLayout Class

Inherits from `Layout`.

### Methods

- `GridLayout(float x, float y, float width, float height, int rows, int columns, float spacing)`: Constructor.
- `void AddControl(std::unique_ptr<Control> control, int row, int column)`: Adds a control to the grid layout at the specified row and column.

## TableLayout Class

Inherits from `Layout`.

### Methods

- `TableLayout(float x, float y, float width, float height, int rows, int columns, float spacing)`: Constructor.
- `void SetHeader(int column, const std::wstring& header)`: Sets the header text for a column.
- `void SetCell(int row, int column, std::unique_ptr<Control> control)`: Sets the control for a cell in the table.

## TabControl Class

Inherits from `Control`.

### Methods

- `TabControl(float x, float y, float width, float height)`: Constructor.
- `void AddTab(std::unique_ptr<TabPage> tabPage)`: Adds a tab page to the control.

## EventListener Class

Base class for event listeners.

### Methods

- `virtual void OnEvent(const Event &event)`: Event handler method. Override this method to handle events.

## Event Class

Represents an event.

### Methods

- `EventType GetType() const`: Returns the event type.

## Enums

- `TextAlignment`: Text alignment values (`Left`, `Center`, `Right`).
- `SliderStyle`: Slider style values (`Linear`, `Circular`).