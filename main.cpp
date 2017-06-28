#include <QCoreApplication>

#include "bloom_filter.h"
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bloom_parameters parameters;
    parameters.projected_element_count = 1000;
    parameters.false_positive_probability = 0.0001;
    parameters.random_seed = 0xA5A5A5A5;

    if (!parameters) {
        qDebug() << "Error - Invalid set of bloom filter parameters!";
        return 1;
    }

    parameters.compute_optimal_parameters();
    bloom_filter filter(parameters);

    QFile data_file(QCoreApplication::applicationDirPath() + "/bfdata");
    if (data_file.exists()) {
        filter.load_file(data_file);
    }

    filter.insert("a");
    filter.insert("bb");
    filter.insert("ccc");

    if (filter.contains("a")) {
        qDebug() << "contains a";
    }

    if (filter.contains("abc")) {
        qDebug() << "contains abc";
    } else {
        qDebug() << "not contains abc";
    }

    return a.exec();
}
