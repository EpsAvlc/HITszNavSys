#include "UI/tools.h"
#include "campus_graph.h"
#include "campus_graph_drawer.h"
#include <iostream>

using namespace std;
int main()
{
    CampusGraph cg;
    CampusGraphDrawer cgd(cg);
    cgd.Spin();
    // char c;
    // cin.get(c);
    // cout << c << endl;
    return 0;
}
