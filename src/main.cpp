#include "infrastructure/repositories/sqlitedatabase.h"
#include "infrastructure/repositories/sqlitestudentrepository.h"
#include "infrastructure/repositories/sqlitesubjectrepository.h"

#include "application/handlers/addstudenthandler.h"
#include "application/handlers/removestudenthandler.h"
#include "application/handlers/editstudenthandler.h"
#include "application/handlers/addsubjecthandler.h"
#include "application/handlers/removesubjecthandler.h"
#include "application/handlers/renamesubjecthandler.h"
#include "application/handlers/getallstudentshandler.h"
#include "application/handlers/getallsubjectshandler.h"

#include "presentation/windows/mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("GradesApp");
    app.setOrganizationName("PW");

    // ── Infrastructure ────────────────────────────────────────────────────────
    const QString dbPath = QDir::currentPath() + "/grades.db";
    Infrastructure::SqliteDatabase db(dbPath, "grades");
    Infrastructure::SqliteSubjectRepository subjectRepo(db.connectionName());
    Infrastructure::SqliteStudentRepository studentRepo(db.connectionName());

    // ── Application ───────────────────────────────────────────────────────────
    Application::AddStudentHandler addStudent(studentRepo);
    Application::RemoveStudentHandler removeStudent(studentRepo);
    Application::EditStudentHandler editStudent(studentRepo);
    Application::AddSubjectHandler addSubject(subjectRepo);
    Application::RemoveSubjectHandler removeSubject(subjectRepo, studentRepo);
    Application::RenameSubjectHandler renameSubject(subjectRepo, studentRepo);
    Application::GetAllStudentsHandler getAllStudents(studentRepo);
    Application::GetAllSubjectsHandler getAllSubjects(subjectRepo);

    // ── Presentation ──────────────────────────────────────────────────────────
    Presentation::MainWindow window(
        addStudent, removeStudent, editStudent,
        addSubject, removeSubject, renameSubject,
        getAllStudents, getAllSubjects
    );
    window.show();

    return app.exec();
}
