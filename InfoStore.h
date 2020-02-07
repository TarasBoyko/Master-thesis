#ifndef INFOSTORE_H
#define INFOSTORE_H

class BaseButton;
class AreaButton;
class GreenButton;
class SearchForm;

#include <header.h>

class InfoStore : public QObject
{
    Q_OBJECT

    friend class FunctionForm;
    friend class SearchForm;
public:
    struct FunctionInfo
    {
        int id;
        QString shortDescription;
        set<int> associatedGreenButtonsId;
        // for sorting function info to record into file in order
        bool operator<(const FunctionInfo& x) const { return id < x.id; }
    };

    vector<AreaButton*> areaButtons;
private:

    SearchForm* const parentOfElements; // in this class
    // area button, that includes current slide
    // cannot delete, because intoing into AreaButton code delete all AreaButtons in current slide
    AreaButton* intoingAreaButton;


    vector<GreenButton*> greenButtons;
    //vector<GreenButton*> pressedGreenButtons;

    string kAreaChapterInInfoFile = "AreaButtons";
    string kGreenChapterInInfoFile = "GreenButtons";
    string kFlashChapterInInfoFile = "FlashButtons";
    string kFunctionChapterInInfoFile = "Functions";


    vector<FunctionInfo> functions;
    vector<FunctionInfo> selectedFunctions;



public:
    InfoStore(SearchForm * const parentOfElements_);
    void SetIntoingAreaButton(AreaButton *newIntoingAreaButton);
    void Clear();
    void IntersectSelectedFunctions(GreenButton * const pressedButton);
    void MergeSelectedFunctions();
    void FillFromInfoFile(); private:
        void ReadBaseButtonDataFromInfoFile(char *&rp,
                                            QString& text,
                                            int& identidier,
                                            QRect& rect
                                            ); public:
    void RecordDataIntoInfoFile();

    void DeleteGreenButton(GreenButton* const deletingButton);
    void DeleteAreaButton(AreaButton* const deletingButton);


    bool IsAllGreenButtonsUnpressed() const;
    bool IsFunctionWithSingleAssocGreenButton(GreenButton* button, FunctionInfo &poorFunction);

    vector<FunctionInfo> GetSelectedFunctions() const;

    int GetNewAreaButtonId() const;
    int GetNewGreenButtonId() const;
    int GetNewFunctionId() const;
    FunctionInfo& GetReferenceToFunctionById(const int& id);

    set<int> GetPressedGreenButtonIds() const;

    void AddBaseButton(BaseButton* insertingButton);
    void AddFunction(FunctionInfo newFunction);
    void UnCheckPressedGreenButtons();
    void DeleteFunctionById(const int& id);
signals:
    void SelectedFunctionsUpdated();
public slots:

};

#endif // INFOSTORE_H
