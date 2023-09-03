

#include <QtWidgets>


class Field : public QWidget {

public:
	Field(QWidget* parent = nullptr) : QWidget(parent) {
		gridGroupBox = new QGroupBox(tr("Grid layout"), this);
	}
	~Field() {}


protected:

	QGroupBox* gridGroupBox;

	void paintEvent(QPaintEvent* pe) {
		
		gridGroupBox->show();
		

	}


};
