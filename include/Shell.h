#include "DisplayablesManager.h"
#include "String.h"

class CommandsManager;
class Command;

#define PROMPT	"Hey! type help to print usage> "

class	Shell : public Displayable
{
public:
	Shell(CommandsManager* cmdManager);
	void start();
	virtual void addValToBuffer(char value) override;
	void printStroke(char strokeValue);

private:
	CommandsManager* m_cmdManager;

	void parseBuffer() override;
	String	parseCmdName();
	void setArgsToCmd(Command& cmd);
};
