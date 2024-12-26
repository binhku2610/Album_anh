#include <iostream>
#include <sstream>
#include <string>
#include <fstream> // Thư viện hỗ trợ thao tác với tệp tin
using namespace std;

struct Photo {
    string name;  // Tên ảnh
    string date;  // Ngày chụp (dd-mm-yyyy)
    float size;   // Dung lượng ảnh (MB)
};

// Hàm loại bỏ ảnh trùng lặp
void removeDuplicatePhotos(Photo photos[], int& photoCount) {
    for (int i = 0; i < photoCount; i++) {
        for (int j = i + 1; j < photoCount; j++) {
            if (photos[i].name == photos[j].name) {
                for (int k = j; k < photoCount - 1; k++) {
                    photos[k] = photos[k + 1];
                }
                photoCount--;
                j--;
            }
        }
    }
}
// Hàm nhập thông tin từ tệp
void loadPhotosFromFile(const string& filename, Photo photos[], int& photoCount) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Khong the mo tep " << filename << endl;
        return;
    }
    photoCount = 0; // Khởi tạo lại số lượng ảnh
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        Photo photo;
        // Đọc tên ảnh, nếu không có để trống
        if (!getline(ss, photo.name, ',')) {
            photo.name = "";
        }
        // Đọc ngày chụp, nếu không có để trống
        if (!getline(ss, photo.date, ',')) {
            photo.date = "";
        }
        // Đọc dung lượng, nếu không có đặt mặc định là 0
        if (!(ss >> photo.size)) {
            photo.size = 0;
        }
        // Chỉ thêm ảnh vào mảng nếu có ít nhất một trường không rỗng
        if (!photo.name.empty() || !photo.date.empty() || photo.size != 0) {
            photos[photoCount++] = photo;
        }
    }
    inputFile.close();
    cout << "Da tai thanh cong " << photoCount << " anh tu tep!" << endl;
}

// Hàm hiển thị danh sách ảnh
void displayPhotos(Photo photos[], int photoCount) {
    if (photoCount == 0) {
        cout << "Album hien tai khong co anh nao!" << endl;
    } else {
        cout << "Danh sach anh trong album:" << endl;
        for (int i = 0; i < photoCount; i++) {
            cout << i + 1 << ". Ten: " << photos[i].name
                 << ", Ngay chup: " << photos[i].date
                 << ", Dung luong: " << photos[i].size << " MB" << endl;
        }
    }
}

// Hàm tìm kiếm ảnh
void searchPhotos(Photo photos[], int photoCount) {
    cout << "Nhap ten anh de tim kiem: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < photoCount; i++) {
        if (photos[i].name == query) {
            cout << "Tim thay: Ten: " << photos[i].name
                 << ", Ngay chup: " << photos[i].date
                 << ", Dung luong: " << photos[i].size << " MB" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay anh phu hop!" << endl;
    }
}

// Hàm thêm ảnh mới
void addPhotos(Photo photos[], int& photoCount, const string& outputFile) {
    int n;
    cout << "Nhap so luong anh muon them: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        Photo newPhoto;
        cout << "Nhap thong tin anh thu " << i + 1 << ":\n";

        cout << "Nhap ten anh: ";
        getline(cin, newPhoto.name);

        cout << "Nhap ngay chup (dd-mm-yyyy): ";
        getline(cin, newPhoto.date);

        cout << "Nhap dung luong (MB): ";
        cin >> newPhoto.size;
        cin.ignore();

        photos[photoCount++] = newPhoto;
    }
}

// Hàm xóa ảnh
void deletePhoto(Photo photos[], int& photoCount) {
    cout << "Nhap ten anh de xoa: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool deleted = false;
    for (int i = 0; i < photoCount; i++) {
        if (photos[i].name == query) {
            for (int j = i; j < photoCount - 1; j++) {
                photos[j] = photos[j + 1];
            }
            photoCount--;
            deleted = true;
            cout << "Da xoa anh: " << query << endl;
            break;
        }
    }

    if (!deleted) {
        cout << "Khong tim thay anh de xoa!" << endl;
    }
}

// Hàm chỉnh sửa thông tin ảnh
void editPhoto(Photo photos[], int photoCount) {
    cout << "Nhap ten anh de chinh sua: ";
    string query;
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < photoCount; i++) {
        if (photos[i].name == query) {
            found = true;
            cout << "Nhap thong tin moi cho anh:\n";

            cout << "Nhap ten moi (bo trong neu khong doi): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                photos[i].name = newName;
            }

            cout << "Nhap ngay chup moi (dd-mm-yyyy, bo trong neu khong doi): ";
            string newDate;
            getline(cin, newDate);
            if (!newDate.empty()) {
                photos[i].date = newDate;
            }

            cout << "Nhap dung luong moi (MB, nhap -1 neu khong doi): ";
            float newSize;
            cin >> newSize;
            cin.ignore();
            if (newSize >= 0) {
                photos[i].size = newSize;
            }

            cout << "Da cap nhat thong tin anh!\n";
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay anh de chinh sua!" << endl;
    }
}

int main() {
    Photo photos[100]; // Mảng lưu trữ tối đa 100 ảnh
    int photoCount = 0; // Số lượng ảnh hiện tại

    string inputFile = "input.txt"; // Sử dụng file mặc định

    loadPhotosFromFile(inputFile, photos, photoCount); // Đọc dữ liệu từ tệp

    int choice;
    do {
        cout << "\nQuan ly album anh:\n";
        cout << "1. Hien thi danh sach anh\n";
        cout << "2. Loai bo anh trung lap\n";
        cout << "3. Tim kiem anh\n";
        cout << "4. Them anh moi\n";
        cout << "5. Xoa anh\n";
        cout << "6. Chinh sua thong tin anh\n";
        cout << "7. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayPhotos(photos, photoCount);
                break;
            case 2:
                removeDuplicatePhotos(photos, photoCount);
                cout << "Da loai bo anh trung lap!\n";
                break;
            case 3:
                searchPhotos(photos, photoCount);
                break;
            case 4:
                addPhotos(photos, photoCount, inputFile);
                break;
            case 5:
                deletePhoto(photos, photoCount);
                break;
            case 6:
                editPhoto(photos, photoCount);
                break;
            case 7:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 7);
    return 0;
}