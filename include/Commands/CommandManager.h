class Command
{
private:
	String name;
	String args;
	uint16_t nameLen;
	uint8_t argsCount;

public:
	String getArg(uint8_t argNb);

	String getName() const
	{
		return name;
	}
};

// Class to handle the commands as a collection.
class CommandManager
{
public:
	CommandManager();

private:
	static const uint8_t cmdMax = 5;
	uint8_t cmdCount;
	Command* commands[cmdMax];

public:
	void addCommand(Command *newDisplayable);
};
