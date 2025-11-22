#include "CoreApp.h"
#include "Utility/ArgumentParser.h"

CoreApp* g_pApp = CoreApp::Get();

int main(int argc, char** argv)
{
    if (!g_pApp)
    {
        return EXIT_FAILURE;
    }

    if (argc >= 2)
    {
        /*
        if (!strcmp(argv[1], "-gen_hashes"))
        {
            ::printf("Server launched with -gen_hashes flag!1!!!\n");
        }
        */

        ArgumentParser::Get().Init(argc, argv);
        ArgumentParser::Get().Parse();
    }
    
    //::printf("int main got %d argc %s\n", argc, argv[1]);

    g_pApp->Init();
    g_pApp->Main();

    return EXIT_SUCCESS;
}