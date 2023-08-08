package com.zybooks.weightlosskcl;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.ArrayList;

public class DBHandlerWeight extends SQLiteOpenHelper {

    //Creating all the variables for the user login database
    //This is for the database name
    private static final String DB_NAME = "weight.db";

    //This if for the database version
    private static final int DB_VERSION = 1;

    //This is for the table name
    private static final String TABLE_NAME = "weightInfo";

    //This is for the id column. This will notate how many weight entries there are in the data base. Starting with 1,
    //and moving up automatically. the auto feature will be called later in the code.
    private static final String ID_COL = "id";

    //This is for the weight column
    private static final String WEIGHT_COL = "weight";

    //This is for the date column
    private static final String DATE_COL = "date";


    //This is the constructor the db handler
    public DBHandlerWeight(Context context) {
        super(context, DB_NAME, null, DB_VERSION);
    }

    //This will create the database running an sqlite query
    @Override
    public void onCreate(SQLiteDatabase db) {
        //These will set our column names as well as auto increment the id column
        String query = "CREATE TABLE " + TABLE_NAME + " ("
                + ID_COL + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + DATE_COL + " TEXT,"
                + WEIGHT_COL + " TEXT)";

        //This will execute the above query
        db.execSQL(query);
    }

    //this will add the new weight to the database
    public void addNewWeight(String weightWeight, String weightDate) {

        //Calls database so we can write information to it
        SQLiteDatabase db = this.getWritableDatabase();

        //create variable for a new weight
        ContentValues values = new ContentValues();

        //this passes the values as well as the keys for the values
        values.put(DATE_COL, weightDate);
        values.put(WEIGHT_COL, weightWeight);

        //this passes the values to the database table
        db.insert(TABLE_NAME, null, values);

        //close the database after info is written to it
        db.close();
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        //This will check if the table already exists
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
}
