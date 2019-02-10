#include "DisplayablesManager.h"
#include "String.h"

#define PROMPT	"Hey! type help to print usage> "
#define CMD_MAX	5

// Commands names
#define REBOOT	"reboot"
#define GODTAKE	"godtake"
#define GODGIVE	"godgive"

class	Shell : public Displayable
{
public:
	Shell();
	void start();
	virtual void addValToBuffer(char value) override;
	void addCommand(String *cmd);
	void printStroke(char strokeValue);

	struct	Cmd
	{
		Cmd();

		String name;
		String args;
		uint16_t nameLen;
		uint8_t argsCount;

		String getArg(uint8_t argNb);
	};

private:
	String *commands[CMD_MAX];
	void parseBuffer() override;
	void getCmdName(Cmd& cmd);
	void getArgs(Cmd& cmd);
	bool isKnownCmd(const String& cmd);
	bool execCmd(Cmd& currentCmd);
	uint32_t cmdCount;

	//	Commands routines
	void reboot();
	void printBytesAsChars(uint32_t start);
	void hexMemoryDump(uint32_t start, uint32_t end);
	void writeToMemory(String& str, uint32_t addr);
};
