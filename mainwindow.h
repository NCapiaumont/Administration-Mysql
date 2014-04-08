#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QListWidgetItem>
#include <QSqlTableModel>
/*!
 *  \brief     Classe MainWindow "mainwindow.h"
 *  \details   Cette classe est la classe MainWindow
 *  \author    Nicolas Capiaumont
 *  \version   1
 *  \date      12/12/13
 *  \copyright GNU Public License.
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /*!
     * \brief MainWindow(QWidget *parent = 0)
     * \param QWidget parent
     * \detail constructeur de la mainwindow
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    /*!
     * \brief void on_pushButton_clicked()
     * \detail
     */
    void on_pushButton_clicked();
    /*!
     * \brief void on_lineEditAdresse_cursorPositionChanged()
     * \detail
     */
    void on_lineEditAdresse_cursorPositionChanged();
    /*!
     * \brief void on_lineEditPort_cursorPositionChanged()
     * \detail
     */
    void on_lineEditPort_cursorPositionChanged();
    /*!
     * \brief void on_lineEditNomU_cursorPositionChanged()
     * \detail
     */
    void on_lineEditNomU_cursorPositionChanged();
    /*!
     * \brief void on_lineEditMdp_cursorPositionChanged()
     * \detail
     */
    void on_lineEditMdp_cursorPositionChanged();
    /*!
     * \brief void on_listWidgetConnexion_itemClicked(QListWidgetItem *item)
     * \param QListWidgetItem item
     * \detail
     */
    void on_listWidgetConnexion_itemClicked(QListWidgetItem *item);
    /*!
     * \brief void on_tabWidget_currentChanged(int index)
     * \param int index
     * \detail
     */
    void on_tabWidget_currentChanged(int index);
    /*!
     * \brief void on_comboBoxTables_currentIndexChanged()
     * \detail
     */
    void on_comboBoxTables_currentIndexChanged();
    /*!
     * \brief void on_textEditRequette_selectionChanged()
     * \detail
     */
    void on_textEditRequette_selectionChanged();
    /*!
     * \brief void on_pushButtonEnvoyerRequette_clicked()
     * \detail
     */
    void on_pushButtonEnvoyerRequette_clicked();
    /*!
     * \brief void on_pushButtonParcourirScipt_clicked()
     * \detail
     */
    void on_pushButtonParcourirScipt_clicked();
    /*!
     * \brief void on_pushButtonConnection_clicked()
     * \detail
     */
    void on_pushButtonConnection_clicked();
    /*!
     * \brief void on_pushButtonNouvelleBase_clicked()
     * \detail
     */
    void on_pushButtonNouvelleBase_clicked();
    /*!
     * \brief void on_lineEditNomNouvelleBase_textChanged()
     * \detail
     */
    void on_lineEditNomNouvelleBase_textChanged();
private:
    /*!
     * \brief ui
     */
    Ui::MainWindow *ui;
    /*!
     * \brief base
     * \detail déclaration de la base de donnée
     */
    QSqlDatabase base;
    /*!
     * \brief connctBase()
     * \detail connexion a la base de donnée
     */
    void connctBase();
    /*!
     * \brief void CloseBase()
     * \detail ferme la connexion avec la base de donnée
     */
    void CloseBase();
    /*!
     * \brief void connectIfPossible()
     * \detail
     */
    void connectIfPossible();
    /*!
     * \brief void chargerTables()
     * \detail
     */
    void chargerTables();
    /*!
     * \brief void chargerRequette()
     * \detail
     */
    void chargerRequette();
    /*!
     * \brief QSqlTableModel modelTable
     */
    QSqlTableModel * modelTable;
    /*!
     * \brief QSqlTableModel modelReq
     */
    QSqlQueryModel * modelReq;
    /*!
     * \brief bool connexionOK()
     * \return renvoie vrai si la connexion à était effectué
     */
    bool connexionOK();
};
#endif // MAINWINDOW_H
