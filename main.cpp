#include "UI/tools.h"
#include "campus_graph.h"
#include <iostream>

void SetTitle()
{
}

int main()
{
    CampusGraph cg;
    CampusGraphDrawer cgd(cg);
    cgd.Spin();
    return 0;
}
