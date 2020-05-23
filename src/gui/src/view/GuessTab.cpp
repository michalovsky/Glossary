#include "GuessTab.h"

#include <QDebug>

#include "WordDescriptionDialog.h"
#include "ui_GuessTab.h"
#include "utils/GetProjectPath.h"

namespace
{
constexpr auto noneDictionaryName = "none";
const auto resourceDirectoryPath = utils::getProjectPath("glossary") + "src/gui/resources/";
const auto incorrectAnswerIconPath = resourceDirectoryPath + "incorrectAnswer.png";
const auto correctAnswerIconPath = resourceDirectoryPath + "correctAnswer.png";
const auto nextIcon = resourceDirectoryPath + "next.png";
}

namespace glossary::gui::view
{

GuessTab::GuessTab(QWidget* parent) : QWidget(parent), ui(new Ui::GuessTab)
{
    ui->setupUi(this);
    ui->boxWithDictionaryNames->setModel(&dictionaryNamesToRandomizeWordFromModel);
    ui->buttonNextRandomWord->setIcon(QIcon(nextIcon.c_str()));
}

GuessTab::~GuessTab()
{
    delete ui;
}

void GuessTab::setAvailableDictionaryNames(const QList<QString>& dictionaryNames)
{
    dictionaryNamesToRandomizeWordFrom = dictionaryNames;
    dictionaryNamesToRandomizeWordFrom.push_front(noneDictionaryName);
    dictionaryNamesToRandomizeWordFromModel.setStringList(dictionaryNamesToRandomizeWordFrom);
}

void GuessTab::onNextRandomWordReceived(const QString& randomPolishWord) const
{
    ui->editPolishWord->setText(randomPolishWord);
}

void GuessTab::onWordDescriptionReceived(const WordDescription& wordDescription) const
{
    WordDescriptionDialog wordDescriptionDialog{nullptr, wordDescription};
    wordDescriptionDialog.show();
    wordDescriptionDialog.exec();
}

void GuessTab::onCheckedTranslationVerdictReceived(bool translationCorrect) const
{
    if (translationCorrect)
    {
        auto correctAnswerIcon = QPixmap(correctAnswerIconPath.c_str());
        int width = ui->labelWithCorrectIcon->width();
        int height = ui->labelWithCorrectIcon->height();
        ui->labelWithCorrectIcon->setPixmap(correctAnswerIcon.scaled(width, height, Qt::KeepAspectRatio));
        ui->labelCheckCorrectness->setText("Correct answer!");
    }
    else
    {
        auto incorrectAnswerIcon = QPixmap(incorrectAnswerIconPath.c_str());
        ui->labelWithCorrectIcon->setPixmap(incorrectAnswerIcon);
        ui->labelCheckCorrectness->setText("Incorrect answer");
    }
}

void GuessTab::on_buttonNextRandomWord_clicked() const
{
    if (selectedDictionaryName)
    {
        emit notifyNextRandomWordFromDictionaryClicked(*selectedDictionaryName);
        return;
    }
    emit notifyNextRandomWordClicked();
}

void GuessTab::on_boxWithDictionaryNames_activated(const QString& dictionaryName)
{
    if (dictionaryName != noneDictionaryName)
    {
        selectedDictionaryName = dictionaryName;
    }
    else
    {
        selectedDictionaryName = boost::none;
    }
}

void GuessTab::on_buttonCheckWordDescription_clicked()
{
    const auto currentlyInsertedEnglishWord = ui->editEnglishTranslation->text();
    emit notifyCheckWordDescriptionClicked(currentlyInsertedEnglishWord);
}

void GuessTab::on_buttonCheckTranslationCorrectness_clicked()
{
    const auto currentPolishWord = ui->editPolishWord->text();
    const auto currentlyInsertedEnglishWord = ui->editEnglishTranslation->text();
    emit notifyCheckTranslationCorrectnessClicked(currentPolishWord, currentlyInsertedEnglishWord.trimmed());
}

}