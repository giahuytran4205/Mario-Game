#include "TextView.hpp"
#include "FontManager.hpp"

void TextView::wrapText()
{
    float maxWidth = Object::m_transform.getRect().width;
    float maxHeight = Object::m_transform.getRect().height;

    unsigned int textSize = 1;

    std::vector<std::string> lines;
    std::istringstream fullStream(this->getString());
    std::string line;

    while (std::getline(fullStream, line)) 
    {
        lines.push_back(line);
    }

    while (true) 
    {
        std::string wrappedText;
        this->setCharacterSize(textSize);

        for (const std::string& originalLine : lines)
        {
            std::string currentLine;
            std::istringstream wordStream(originalLine);
            std::string word;

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

            wrappedText += currentLine + "\n";
        }

        this->setString(wrappedText);

        if (this->getLocalBounds().height >= maxHeight * m_ratioCharSizeTableHeight) 
        {
            break;
        }

        textSize += 1;
    }

    this->setCharacterSize(textSize);
    sf::FloatRect textBounds = this->getGlobalBounds();
	this->setPosition(Object::m_transform.getRect().left + (Object::m_transform.getRect().width - textBounds.width) / 2, Object::m_transform.getRect().top + (Object::m_transform.getRect().height - textBounds.height) / 2);
}

TextView::TextView(Object* parent)
{
	//this->setParent(parent);

    this->setRenderOrder(TEXTVIEW_DEFAUTL_RENDER_ORDER);

	configure(sf::Vector2f(0, 0), sf::Vector2f(100, 50), "TextView", FontManager::getInstance()->getFont("ARIAL"));
}

TextView::TextView(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font, Object* parent)
{
	//this->setParent(parent);

    this->setRenderOrder(TEXTVIEW_DEFAUTL_RENDER_ORDER);

	configure(tablePosition, tableSize, content, font);
}

TextView::~TextView()
{
}

void TextView::configure(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font)
{
    Object::m_transform.getRect() = FRect(tablePosition.x, tablePosition.y, tableSize.x, tableSize.y);

	m_ratioCharSizeTableHeight = DEFAULT_RATIO_CHAR_SIZE_TABLE_HEIGHT;

	this->setFont(font);

	this->setString(content);

	this->setFillColor(sf::Color::Black);

	this->setStyle(sf::Text::Regular);

	this->wrapText();
}

void TextView::setRatioCharacterSizeTableHeight(float ratio)
{
	if (ratio <= 0 || ratio >= 1)
	{
		throw std::out_of_range("Ratio must be in the range (0, 1)");
	}

	m_ratioCharSizeTableHeight = ratio;
    this->wrapText();
}

void TextView::setTable(const FRect& table)
{
	if (table.left < 0 || table.top < 0)
	{
		throw std::out_of_range("Table position must be positive");
	}

	if (table.width < 0 || table.height < 0)
	{
		throw std::out_of_range("Table size must be positive");
	}

    Object::m_transform.getRect() = table;
    this->wrapText();
}

void TextView::setTablePosition(const sf::Vector2f& tablePosition)
{
	if (tablePosition.x < 0 || tablePosition.y < 0)
	{
		throw std::out_of_range("Table position must be positive");
	}

    Object::m_transform.getRect().left = tablePosition.x;
    Object::m_transform.getRect().top = tablePosition.y;
    this->wrapText();
}

void TextView::setTableSize(const sf::Vector2f& tableSize)
{
	if (tableSize.x < 0 || tableSize.y < 0)
	{
		throw std::out_of_range("Table size must be positive");
	}

    Object::m_transform.getRect().width = tableSize.x;
    Object::m_transform.getRect().height = tableSize.y;
    this->wrapText();
}

const FRect& TextView::getTable() const
{
	return Object::m_transform.getRect();
}

void TextView::render()
{
    sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
    window.draw(*this);
}
