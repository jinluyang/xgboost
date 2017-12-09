//the label should be 0,1,2,3...
float evaluate(std::vector<xgboost::bst_float>y_pred,std::vector<xgboost::bst_float> y_ref, int num_class)
{
    assert(y_pred.size()==y_ref.size());
    float right=0;
    int i;
    //confusion matrix
    std::vector<std::vector<int> > conf_mat(num_class,std::vector<int>(num_class));
    for ( i=0;i<(int)(y_pred.size());i++)
    {
//            std::cout << "ypred"<< y_pred[i]<< "y_ref:"<< y_ref[i]<< std::endl;
        conf_mat[y_pred[i]][y_ref[i]] += 1;
        if (y_ref[i]==y_pred[i])
            right+=1;

    }
    std::cout << "accuracy="<< right/(float)(y_ref.size())<< std::endl;
    //print confusion matrix
    std::cout <<"confusion matrix:"<< std::endl;
    std::cout <<"prediction"<<'\\'<<" real value" ;
//    std::cout.width(5);
    for (i=0;i< num_class;i++)
        std::cout << "   "<< i;
    std::cout << std::endl;
    for ( i=0;i<num_class;i++)
    {
        std::cout<<"                  " <<i<<"|";
        for (int j=0;j<num_class;j++)
        {
            std::cout << std::setw(3)<< conf_mat[i][j]<< " |";
        }
        std::cout << std::endl;
    }
    return 0;

}
