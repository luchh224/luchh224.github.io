package com.zybooks.weightlosskcl;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.ArrayList;


public class DBHandler extends SQLiteOpenHelper {

    //Creating all the variables for the user login database
    //This is for the database name
    private static final String DB_NAME = "login.db";

    //This if for the database version
    private static final int DB_VERSION = 1;

    //This is for the table name
    private static final String TABLE_NAME = "contactInfo";

    //This is for the id column. This will notate how many contacts there are in the data base. Starting with 1,
    //and moving up automatically. the auto feature will be called later in the code.
    private static final String ID_COL = "id";

    //This is for the name column
    private static final String NAME_COL = "name";

    //This is for the email column
    private static final String EMAIL_COL = "email";

    //This is for the phone number column
    private static final String PHONE_COL = "phone number";

    //This is for the password column
    private static final String PASSWORD_COL = "password";

    //This is the constructor the db handler
    public DBHandler(Context context) {
        super(context, DB_NAME, null, DB_VERSION);
    }

    //This will create the database running an sqlite query
    @Override
    public void onCreate(SQLiteDatabase db) {
        //These will set our column names as well as auto increment the id column
        String query = "CREATE TABLE " + TABLE_NAME + " ("
                + ID_COL + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + NAME_COL + " TEXT,"
                + EMAIL_COL + " TEXT,"
                + PHONE_COL + "TEXT,"
                + PASSWORD_COL + "TEXT)";

        //This will execute the above query
        db.execSQL(query);
    }

    //This is going to add the new contact to the database
    public void addNewContact(String contactName, String contactEmail, String contactPhoneNumber, String contactPassword) {

        //Calling the database so we can write information to it
        SQLiteDatabase db = this.getWritableDatabase();

        //creating a variable for new contact value

        ContentValues values = new ContentValues();

        //This will pass the values as well as the keys for the values
        values.put(NAME_COL, contactName);
        values.put(EMAIL_COL, contactEmail);
        values.put(PHONE_COL, contactPhoneNumber);
        values.put(PASSWORD_COL, contactPassword);

        //This will pass the values to the tables
        db.insert(TABLE_NAME, null, values);

        //Last step is to close the database
        db.close();
    }

    //Creating a new method for reading the contact info
    public ArrayList<LoginModal> readContacts() {

        //this will create another database to read the already created database
        SQLiteDatabase db = this.getReadableDatabase();

        //this is going to allow data to be read from the database
        Cursor cursorContacts
                = db.rawQuery("SELECT * FROM " + TABLE_NAME, null);

        //this will create a new array list
        ArrayList<LoginModal> contactModalArrayList
                = new ArrayList<>();

        //this will start to search at the first position
        if (cursorContacts.moveToFirst()) {
            do {
                //thi is going to add data
                contactModalArrayList.add(new LoginModal(
                        cursorContacts.getString(1),
                        cursorContacts.getString(4),
                        cursorContacts.getString(2),
                        cursorContacts.getString(3)));
            } while (cursorContacts.moveToNext());
            //the above moves to the next entry
        }
        cursorContacts.close();
        return contactModalArrayList;
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        //This will check if the table already exists
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
}


