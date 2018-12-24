package hw7;

/**
 * Created by ORHAN on 18.12.2017.
 */


public interface GTUSetInt <T> {

    /**
     *Checks if Set Set is empty
     * @return true if Set is not empty.False if else.
     */
    public boolean empty();

    /**
     *
     * @return Current size of the  Set array.
     */
    public int size();

    /**
     *
     * @return Current capacity of the Set array.
     */
    public int max_size();

    /**
     *Put new elements into Set array.Checks if it exist in the Set first.
     * @param e  New element to be inserted
     */
    public void insert(T e);

    /**
     *
     * @param other Other Set Object that contains a Set array.Method checks for 
     * intersections of 2 Set array.
     * @return A Set object.
     */
    GTUSetInt<T> intersection(GTUSetInt<T> other );

    /**
     *Finds and deletes the element of off the Set array.
     * @param e Element to be erased off of the Set Array.
     */
    public void erase(T e);

    /**
     *Erases every elements in the list.
     */
    public void clear();

    /**
     *
     * @param e Element to be find and set the iterotor to it
     * @return A GTUIterator object.
     */
    public GTUIterator<T> find(T e);

    /**
     *
     * @param e Element to be check if it exist and how manyç
     * @return  The amount of element found in the Set array.It is a set so it's
     * either 1 or 0.
     */
    public int count(T e);

    /**
     *Sets iterator to the start of the Set array.
     * @return A GTUIterator object.
     */
    public GTUIterator<T> begin();

    /**
     *Sets iterator to the end of the Set array.
     * @return A GTUIterator object.
     */
    public GTUIterator<T> end();

}
