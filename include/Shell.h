#include "DisplayablesManager.h"
#include "String.h"

#define PROMPT	"Hey! type help to print usage> "
#define NB_CMD	5

// Commands
#define REBOOT "reboot"

class	Shell : public IDisplayable
{
public:
	Shell();
	void start();
	void reboot();
	virtual void addValToBuffer(char value) override;
	void addCommand(String *cmd);
	void printStroke(char strokeValue);

private:
	String *commands[NB_CMD];
	void parseBuffer() override;
	bool isKnownCmd(const String& cmd);
	bool execCmd(String& cmd);
};
