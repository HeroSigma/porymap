#include <QTest>
#include "test_am95_importer.cpp"
#include "test_am95_map_parser.cpp"

int main(int argc, char **argv) {
    int status = 0;
    {
        TestAm95Importer tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    {
        TestAm95MapParser tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    return status;
}
