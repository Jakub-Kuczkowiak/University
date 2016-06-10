package com.januszsoft.bikerental.backend.dao;

import com.januszsoft.bikerental.backend.models.Issue;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.util.List;

public class IssueDaoImpl implements Dao<Issue> {

  private JdbcTemplate jdbcTemplate;

  public IssueDaoImpl(DataSource dataSource) {
    jdbcTemplate = new JdbcTemplate(dataSource);
  }

  public void saveOrUpdate(Issue issue) {
    if (issue.getId() != null && issue.getId() > 0) {
      String sql = "UPDATE issue SET reportedbyusser=?, bike=?, reportdate=?, finishdate=?, description=? WHERE id=?";

      jdbcTemplate.update(sql, issue.getReportedbyusser(), issue.getBike(),
        issue.getReportdate(), issue.getFinishdate(), issue.getDescription(), issue.getId());
    }
    else {
      String sql = "INSERT INTO issue (reportedbyusser, bike, reportdate, finishdate. description) VALUES (?, ?, ?, ?)";
      jdbcTemplate.update(sql, issue.getReportedbyusser(), issue.getBike(),
        issue.getReportdate(), issue.getFinishdate(), issue.getDescription());
    }
  }

  @Override
  public void delete(Integer issueID) {
    String sql = "DELETE FROM issue WHERE id=?";
    jdbcTemplate.update(sql, issueID);
  }

  @Override
  public Issue get(Integer issueID) {

    String sql = "SELECT * FROM issue WHERE id=" + issueID;
    List answer = jdbcTemplate.query(sql, new BeanPropertyRowMapper(Issue.class));
    if(answer.size() == 0) return null;
    else return (Issue) answer.get(0);

  }

  @Override
  public List<Issue> findall() {
    String sql = "SELECT * FROM issue";
    return jdbcTemplate.query(sql, new BeanPropertyRowMapper(Issue.class));
  }
}

