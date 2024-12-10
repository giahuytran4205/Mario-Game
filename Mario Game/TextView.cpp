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
        if (this->getLocalBounds().height >= maxHeight / 3)
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

TextView::TextView(Object* parent) : m_window(nullptr)
{
	this->setParent(parent);

	m_table = FRect(0.0f, 0.0f, 0.0f, 0.0f);

	this->setFont(sf::Font());

	this->setString("");

	this->setFillColor(sf::Color::Black);

	this->setStyle(sf::Text::Regular);
}

TextView::TextView(const FRect& table, const std::string& content, const sf::Font& font, Object* parent) : m_window(nullptr)
{
	this->setParent(parent);

	m_table = table;

	this->setFont(font);

	this->setString(content);

	this->setFillColor(sf::Color::Black);

	this->setStyle(sf::Text::Regular);

	wrapText();
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

void TextView::configure(const FRect& table, const std::string& content, const sf::Font& font)
{
	m_table = table;

	this->setFont(font);

	this->setString(content);

	this->setCharacterSize(1);

	this->setFillColor(sf::Color::White);

	this->setStyle(sf::Text::Regular);

	wrapText();
}

void TextView::setTable(const FRect& table)
{
	m_table = table;
	wrapText();
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
