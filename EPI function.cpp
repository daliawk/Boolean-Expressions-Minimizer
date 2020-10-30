void EPI()
{
	//need a list of minterms (one column for the decimal value,second column for the true or false)
	//add another column to the minterm with true or false (for being EPI or not) intialized with false, when it is EPI turned true
	//list of all merged minterms (rows for the decimal values, column for the merged values)
	//in the merged list include the merged decimals values
	int exist = 0;
	bool dotheloop = false;
	for (int i = 0; i < listofminterm.size(); i++)
	{
		for (int r = 0; r < listofmerged.size(); r++)
		{
			if (listofminterm[i][0] == listofmerged[r][0])
			{
				exist++;
			}
		}
		if (exist == 1)
		{
			dotheloop = true;
			for (int w = 0; w < listofmerged.size(); w++)
			{
				if (listofminterm[i][0] == listofmerged[w][0])
				{
					listofminterm[i][1] = true;
					EPIlist[w] = listofminterm[w][1];
				}
				
			}
		}
	}
	if (dotheloop == true)
		EPI();
	else
		exit;
}