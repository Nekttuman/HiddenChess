#include "RoomCreationWidget.h"

RoomCreationWidget::RoomCreationWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(this, &RoomCreationWidget::fieldsCorrect_signal,
		this, &RoomCreationWidget::allowRoomCreation_slot);
}

RoomCreationWidget::~RoomCreationWidget()
{}
