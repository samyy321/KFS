#include "DisplayablesManager.h"
#include "String.h"

#define PROMPT	"Hey! type help to print usage> "
#define NB_CMD	5

// Commands
#define REBOOT "reboot"

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
		String name;
		String args;
		uint16_t nameLen;
		uint8_t argsCount;
	};

private:
	String *commands[NB_CMD];
	void parseBuffer() override;
	void getCmdName(Cmd& cmd);
	void getArgs(Cmd& cmd);
	bool isKnownCmd(const String& cmd);
	bool execCmd(Cmd& currentCmd);
};
