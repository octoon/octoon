#include "setting_main_plane.h"
#include <qlabel.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qcheckbox.h>
#include <qcombobox.h>

SettingMainPlane::SettingMainPlane(QWidget* parent)
	: QWidget(parent)
{
	auto infoLabel = std::make_unique<QLabel>(this);
	infoLabel->setText(u8"�汾��Ϣ");
	infoLabel->setStyleSheet("color: rgb(255,255,255);");

	auto infoButton = std::make_unique<QToolButton>(this);
	infoButton->setText(u8"������");
	infoButton->setStyleSheet("background: rgb(50,50,50); border:2px solid #646464;border-radius:4px;color: rgb(200,200,200);");
	infoButton->setFixedSize(190, 35);

	auto versionLabel = std::make_unique<QLabel>(this);
	versionLabel->setText(u8"��ǰ�汾��v1.0.0");
	versionLabel->setStyleSheet("color: rgb(200,200,200);");

	/*QLabel* startupLabel = new QLabel(this);
	startupLabel->setText(u8"������");
	startupLabel->setStyleSheet("color: rgb(255,255,255);");

	QCheckBox* checkBox = new QCheckBox(this);
	checkBox->setText(u8"�����Զ�����");
	checkBox->setStyleSheet("color: rgb(200,200,200);");

	QLabel* langLabel = new QLabel(this);
	langLabel->setText(u8"����");
	langLabel->setStyleSheet("color: rgb(255,255,255);");

	QComboBox* gamCombo = new QComboBox(this);
	gamCombo->addItem(u8"����");
	gamCombo->setStyleSheet("color: rgb(200,200,200);");
	gamCombo->setFont(QFont("Microsoft YaHei", 9, 50));

	QLabel* powerLabel = new QLabel(this);
	powerLabel->setText(u8"����");
	powerLabel->setStyleSheet("color: rgb(255,255,255);");

	QCheckBox* lowpowerBox = new QCheckBox(this);
	lowpowerBox->setText(u8"�͹���ģʽ");
	lowpowerBox->setStyleSheet("color: rgb(200,200,200);");*/

	QLabel* defaultLabel = new QLabel(this);
	defaultLabel->setText(u8"�ָ�Ĭ������");
	defaultLabel->setStyleSheet("color: rgb(255,255,255);");

	QToolButton* defaultButton = new QToolButton(this);
	defaultButton->setText(u8"�����ָ�");
	defaultButton->setStyleSheet("background: rgb(50,50,50); border:2px solid #646464; border-radius:4px;color: rgb(200,200,200);");
	defaultButton->setFixedSize(190, 35);

	auto layout_ = new QVBoxLayout(this);
	layout_->addWidget(infoLabel.get());
	layout_->addWidget(infoButton.get());
	layout_->addWidget(versionLabel.get());
	/*layout_->addSpacing(10);
	layout_->addWidget(startupLabel);
	layout_->addSpacing(10);
	layout_->addWidget(checkBox);
	layout_->addSpacing(10);
	layout_->addWidget(langLabel);
	layout_->addSpacing(10);
	layout_->addWidget(gamCombo);
	layout_->addSpacing(10);
	layout_->addWidget(powerLabel);
	layout_->addSpacing(10);
	layout_->addWidget(lowpowerBox);*/
	layout_->addSpacing(10);
	layout_->addWidget(defaultLabel);
	layout_->addSpacing(10);
	layout_->addWidget(defaultButton);
	layout_->setContentsMargins(0, 0, 0, 10);
}

SettingMainPlane2::SettingMainPlane2(QWidget* parent)
	: QWidget(parent)
{
	renderLabel = std::make_unique<QLabel>(this);
	renderLabel->setText(u8"��Ⱦ����");
	renderLabel->setStyleSheet("color: rgb(255,255,255);");

	resolutionLabel = std::make_unique<QLabel>(this);
	resolutionLabel->setText(u8"�ֱ���");
	resolutionLabel->setStyleSheet("color: rgb(200,200,200);");

	resolutionCombo = std::make_unique<QComboBox>(this);
	resolutionCombo->addItem(u8"320*240");
	resolutionCombo->addItem(u8"720*480");
	resolutionCombo->addItem(u8"800*480");
	resolutionCombo->addItem(u8"1024*576");
	resolutionCombo->addItem(u8"1280x720");
	resolutionCombo->addItem(u8"1920x1080");
	resolutionCombo->setStyleSheet("color: rgb(200,200,200);");
	resolutionCombo->setFont(QFont("Microsoft YaHei", 9, 50));

	speedLabel = std::make_unique<QLabel>(this);
	speedLabel->setText(u8"֡����");
	speedLabel->setStyleSheet("color: rgb(200,200,200);");

	speedCombo = std::make_unique<QComboBox>(this);
	speedCombo->addItem(u8"24");
	speedCombo->addItem(u8"30");
	speedCombo->addItem(u8"60");
	speedCombo->setStyleSheet("color: rgb(200,200,200);");
	speedCombo->setFont(QFont("Microsoft YaHei", 9, 50));

	layout_ = std::make_unique<QVBoxLayout>(this);
	layout_->addWidget(renderLabel.get());
	layout_->addSpacing(10);
	layout_->addWidget(resolutionLabel.get());
	layout_->addSpacing(10);
	layout_->addWidget(resolutionCombo.get());
	layout_->addSpacing(10);
	layout_->addWidget(speedLabel.get());
	layout_->addSpacing(10);	
	layout_->addWidget(speedCombo.get());
}

SettingMainPlane3::SettingMainPlane3(QWidget* parent)
	: QWidget(parent)
{
}