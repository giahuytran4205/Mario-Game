#include "TextView.hpp"

void TextView::wrapText()
{
    float maxWidth = m_table.width;
    float maxHeight = m_table.height;

    unsigned int textSize = 1;  // Start with character size 1
    unsigned int initialTextSize = textSize;

    // Loop until the height of the local bounds is 1/3 of the table's height or greater
    while (true)
    {
        std::string wrappedText;
        std::string currentLine;
        std::istringstream wordStream(this->getString());

        // Set the current character size to textSize
        this->setCharacterSize(textSize);
        std::string word;

        // Wrap the text into lines based on maxWidth
        while (wordStream >> word)
        {
            std::string tempLine = currentLine + word + " ";
            this->setString(tempLine);

            if (this->getLocalBounds().width > maxWidth)
            {
                wrappedText += currentLine + "\n";
                currentLine = word + " ";
            }
            else
            {
                currentLine = tempLine;
            }
        }

        wrappedText += currentLine;  // Add the last line
        this->setString(wrappedText);  // Set the wrapped text

        // Check if the local bounds (height) is under the 1/3 of table height
        if (this->getLocalBounds().height >= maxHeight * m_ratioCharSizeTableHeight)
        {
            break;  // Break the loop when the height reaches 1/3 of the table height
        }

        textSize += 1;  // Increase text size to zoom in
    }

    // Set the final character size for text zooming
    this->setCharacterSize(textSize);

    // Adjust the origin to center the text
    sf::FloatRect textBounds = this->getLocalBounds();
    this->setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);

    // Set the position to the center of the table
    this->setPosition(m_table.left + m_table.width / 2.0f,
        m_table.top + m_table.height / 2.0f);
}

TextView::TextView(sf::RenderWindow* window, Object* parent) : m_window(window)
{
	this->setParent(parent);

	configure(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "", sf::Font());
}

TextView::TextView(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font, sf::RenderWindow* window, Object* parent) : m_window(window)
{
	this->setParent(parent);

	configure(tablePosition, tableSize, content, font);
}

TextView::~TextView()
{
}

void TextView::setRenderWindow(sf::RenderWindow* window)
{
	if (window == nullptr)
	{
		std::cout << "TextView::setRenderWindow: window is nullptr!" << std::endl;
		return;
	}

	m_window = window;
}

void TextView::configure(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font)
{
	m_table = FRect(tablePosition.x, tablePosition.y, tableSize.x, tableSize.y);

	m_ratioCharSizeTableHeight = DEFAULT_RATIO_CHAR_SIZE_TABLE_HEIGHT;

	this->setFont(font);

	this->setString(content);

	this->setCharacterSize(1);

	this->setFillColor(sf::Color::Black);

	this->setStyle(sf::Text::Regular);

	this->wrapText();
}

void TextView::setRatioCharacterSizeTableHeight(float ratio)
{
	m_ratioCharSizeTableHeight = ratio;
    this->wrapText();
}

void TextView::setTable(const FRect& table)
{
	m_table = table;
    this->wrapText();
}

void TextView::setTablePosition(const sf::Vector2f& tablePosition)
{
	m_table.left = tablePosition.x;
	m_table.top = tablePosition.y;
    this->wrapText();
}

void TextView::setTableSize(const sf::Vector2f& tableSize)
{
	m_table.width = tableSize.x;
	m_table.height = tableSize.y;
    this->wrapText();
}

const FRect& TextView::getTable() const
{
	return m_table;
}

void TextView::render()
{
    if (m_window != nullptr)
    {
		m_window->draw(*this);
    }
}
