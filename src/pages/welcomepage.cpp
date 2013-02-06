/****************************************************************************
 * This file is part of Maui Installer.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QAbstractButton>
#include <QIcon>
#include <QPixmap>

#include "welcomepage.h"
#include "ui_welcomepage.h"
#include "installer.h"

WelcomePage::WelcomePage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::WelcomePage)
{
    setTitle(tr("Welcome"));
    ui->setupUi(this);

    // We need the user to select the language
    registerField(QStringLiteral("language"), ui->languages,
                  "currentRow", "currentRowChanged");
}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::initializePage()
{
    ui->computerIcon->setPixmap(QIcon::fromTheme("start-here").pixmap(196));

    ui->languages->addItem("English");

    // Save the original text, we'll use it when the page is hidden to restore
    // original values
    m_cancelText = wizard()->buttonText(QWizard::CancelButton);
    m_nextText = wizard()->buttonText(QWizard::NextButton);
}

bool WelcomePage::validatePage() const
{
    Installer *installer = qobject_cast<Installer *>(QApplication::instance());
    installer->setLanguage("English");

    return true;
}

void WelcomePage::showEvent(QShowEvent *event)
{
    wizard()->button(QWizard::BackButton)->setVisible(false);
    wizard()->setButtonText(QWizard::CancelButton, tr("Try Maui"));
    wizard()->setButtonText(QWizard::NextButton, tr("Install Maui"));
}

void WelcomePage::hideEvent(QHideEvent *event)
{
    wizard()->button(QWizard::BackButton)->setVisible(true);
    wizard()->setButtonText(QWizard::CancelButton, m_cancelText);
    wizard()->setButtonText(QWizard::NextButton, m_nextText);
}

#include "moc_welcomepage.cpp"
